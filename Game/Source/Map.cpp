
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Scene.h"
#include "Map.h"
#include "Defs.h"
#include "Log.h"
#include "Collisions.h"

#include <math.h>

Map::Map() : Module(), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// Ask for the value of a custom property
int Properties::GetProperty(const char* value, int defaultValue) const
{
	for (int i = 0; i < list.count(); i++) {
		if (strcmp(list.At(i)->data->name.GetString(), value) == 0)
		{
			if (list.At(i)->data->value != defaultValue) return list.At(i)->data->value;
			else return defaultValue;
		}
	}
	return defaultValue;
}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

bool Map::Start() {
	LoadCol();
	return true;
}

// Draw the map (all requried layers)
void Map::Draw()
{
	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;
	
	while (mapLayerItem != NULL) {
		
			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					// L04: DONE 9: Complete the draw function
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
						//now we always use the firt tileset in the list
						TileSet* tileset = mapData.tilesets.start->data;

						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);

						app->render->DrawTexture(tileset->texture,
							pos.x,
							pos.y+4,
							&r);
					}
				}
			}
		mapLayerItem = mapLayerItem->next;
	}
}

// Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * mapData.tileWidth;
		ret.y = y * mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (mapData.tileWidth / 2);
		ret.y = (x + y) * (mapData.tileHeight / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; 
		ret.y = y;
	}
	return ret;
}

iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	// Add orthographic world to map coordinates
	// Add the case for isometric maps to WorldToMap

	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / mapData.tileWidth;
		ret.y = y / mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{

		float halfWidth = mapData.tileWidth * 0.5f;
		float halfHeight = mapData.tileHeight * 0.5f;
		ret.x = int((x / halfWidth + y / halfHeight) / 2);
		ret.y = int((y / halfHeight - (x / halfWidth)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

void Map::ResetPath()
{
	frontier.Clear();
	visited.clear();
	breadcrumbs.clear();
	path.Clear();

	frontier.Push(iPoint(19, 4), 0);
	visited.add(iPoint(19, 4));
	breadcrumbs.add(iPoint(19, 4));

	memset(costSoFar, 0, sizeof(uint) * COST_MAP_SIZE * COST_MAP_SIZE);
}

void Map::DrawPath()
{
	iPoint point;

	// Draw visited
	ListItem<iPoint>* item = visited.start;

	while (item)
	{
		point = item->data;
		TileSet* tileset = GetTilesetFromTileId(26);

		SDL_Rect rec = tileset->GetTileRect(26);
		iPoint pos = MapToWorld(point.x, point.y);

		app->render->DrawTexture(tileset->texture, pos.x, pos.y, &rec);

		item = item->next;
	}

	// Draw frontier
	for (uint i = 0; i < frontier.Count(); ++i)
	{
		point = *(frontier.Peek(i));
		TileSet* tileset = GetTilesetFromTileId(25);

		SDL_Rect rec = tileset->GetTileRect(25);
		iPoint pos = MapToWorld(point.x, point.y);

		app->render->DrawTexture(tileset->texture, pos.x, pos.y, &rec);
	}

	// Draw path
	for (uint i = 0; i < path.Count(); ++i)
	{
		iPoint pos = MapToWorld(path[i].x, path[i].y);
		app->render->DrawTexture(tileX, pos.x, pos.y);
	}

}


int Map::MovementCost(int x, int y) const
{
	int ret = -1;

	if ((x >= 0) && (x < mapData.width) && (y >= 0) && (y < mapData.height))
	{
		int id = mapData.layers.start->next->data->Get(x, y);

		if (id == 26) ret = 20;
		else ret = 1;
	}

	return ret;
}


bool Map::IsWalkable(int x, int y) const
{
	// L10: DONE 3: return true only if x and y are within map limits
	// and the tile is walkable (tile id 0 in the navigation layer)

	bool isWalkable = false;
	if (x >= 0 && y >= 0 && x < mapData.width && y < mapData.height) {

		//gets the second layer
		MapLayer* layer = mapData.layers.start->next->data;
		int tileId = layer->Get(x, y);
		if (tileId != 26) isWalkable = true;
	}

	return isWalkable;
}

void Map::ComputePath(int x, int y)
{
	path.Clear();
	iPoint goal = WorldToMap(x, y);

	// L11: TODO 2: Follow the breadcrumps to goal back to the origin
	// add each step into "path" dyn array (it will then draw automatically)

	path.PushBack(goal);
	int index = visited.find(goal);

	while ((index >= 0) && (goal != breadcrumbs[index]))
	{
		goal = breadcrumbs[index];
		path.PushBack(goal);
		index = visited.find(goal);
	}
}

void Map::ComputePathAStar(int x, int y)
{
	// Compute AStart pathfinding
	finishAStar = false;
	ResetPath();
	path.Clear();
	goalAStar = WorldToMap(x, y);
	path.PushBack(goalAStar);
}

void Map::PropagateBFS()
{
	// DONE 1: If frontier queue contains elements
	// pop the last one and calculate its 4 neighbors
	iPoint curr;
	if (frontier.Pop(curr))
	{
		// For each neighbor, if not visited, add it
		// to the frontier queue and visited list
		iPoint neighbors[4];
		neighbors[0].create(curr.x + 1, curr.y + 0);
		neighbors[1].create(curr.x + 0, curr.y + 1);
		neighbors[2].create(curr.x - 1, curr.y + 0);
		neighbors[3].create(curr.x + 0, curr.y - 1);

		for (uint i = 0; i < 4; ++i)
		{
			if (IsWalkable(neighbors[i].x, neighbors[i].y))
			{
				if (visited.find(neighbors[i]) == -1)
				{
					frontier.Push(neighbors[i], 0);
					visited.add(neighbors[i]);

					// Record the direction to the previous node 
					// with the new list "breadcrumps"
					breadcrumbs.add(curr);
				}
			}
		}
	}
}

void Map::PropagateDijkstra()
{
	// Taking BFS as a reference, implement the Dijkstra algorithm
	// use the 2 dimensional array "costSoFar" to track the accumulated costs
	// on each cell (is already reset to 0 automatically)

	iPoint curr;
	if (frontier.Pop(curr))
	{
		iPoint neighbors[4];
		neighbors[0].create(curr.x + 1, curr.y + 0);
		neighbors[1].create(curr.x + 0, curr.y + 1);
		neighbors[2].create(curr.x - 1, curr.y + 0);
		neighbors[3].create(curr.x + 0, curr.y - 1);

		for (uint i = 0; i < 4; ++i)
		{
			int cost = MovementCost(neighbors[i].x, neighbors[i].y);

			if (cost >= 0)
			{
				cost += costSoFar[curr.x][curr.y];
				if (visited.find(neighbors[i]) == -1 || cost < costSoFar[neighbors[i].x][neighbors[i].y])
				{
					costSoFar[neighbors[i].x][neighbors[i].y] = cost;
					frontier.Push(neighbors[i], cost);
					visited.add(neighbors[i]);
					breadcrumbs.add(curr);
				}
			}
		}
	}
}

void Map::PropagateAStar(int heuristic)
{
	// L12a: TODO 2: Implement AStar algorythm
	// Consider the different heuristics
	iPoint curr;
	if (finishAStar == false && frontier.Pop(curr))
	{
		if (curr == goalAStar)
		{
			finishAStar = true;
			return;
		}

		iPoint neighbors[4];
		neighbors[0].create(curr.x + 1, curr.y + 0);
		neighbors[1].create(curr.x + 0, curr.y + 1);
		neighbors[2].create(curr.x - 1, curr.y + 0);
		neighbors[3].create(curr.x + 0, curr.y - 1);

		for (uint i = 0; i < 4; ++i)
		{
			int cost = MovementCost(neighbors[i].x, neighbors[i].y);

			if (cost >= 0)
			{
				cost += costSoFar[curr.x][curr.y];
				if (visited.find(neighbors[i]) == -1 || cost < costSoFar[neighbors[i].x][neighbors[i].y])
				{
					costSoFar[neighbors[i].x][neighbors[i].y] = cost;
					switch (heuristic)
					{
					case 1: cost += goalAStar.DistanceManhattan(neighbors[i]); break;
					case 2: cost += goalAStar.DistanceNoSqrt(neighbors[i]); break;
					default: cost += goalAStar.DistanceTo(neighbors[i]); break;
					}

					frontier.Push(neighbors[i], cost);
					visited.add(neighbors[i]);
					breadcrumbs.add(curr);
				}
			}
		}
	}
}

// Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = mapData.tilesets.start;
	TileSet* set = item->data;

	for (set; set; item = item->next, set = item->data)
	{
		if (id >= set->firstgid && id < set->firstgid + set->tilecount)
			return set;
	}
	return set;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// Get relative Tile rectangle
	int relativeId = id - firstgid;
	rect.w = tileWidth;
	rect.h = tileHeight;
	rect.x = margin + ((rect.w + spacing) * (relativeId % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relativeId / num_tiles_width));
	
	return rect;
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // Make sure you clean up any memory allocated from tilesets/map
    // Remove all tilesets
	ListItem<TileSet*>* item;
	item = mapData.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	mapData.tilesets.clear();

	// Cleaning up all layer data
	// Remove all layers
	ListItem<MapLayer*>* item2;
	item2 = mapData.layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	mapData.layers.clear();

    return true;
}

// Loading new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

	pugi::xml_document mapFile; 
    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

	// Load general info
    if(ret == true)
    {
        // Create and call a private function to load and fill all your map data
		ret = LoadMap(mapFile);
	}

    // Create and call a private function to load a tileset
    // remember to support more any number of tilesets!
	if (ret == true)
	{
		ret = LoadTileSets(mapFile.child("map"));
	}

	// Iterating all layers and load each of them
	// Load layer info
	if (ret == true)
	{
		ret = LoadAllLayers(mapFile.child("map"));
	}
    
    if(ret == true)
    {
        // LOG all the data loaded iterate all tilesets and LOG everything
		 
		LOG("Successfully parsed map XML file: %s", filename);
		LOG("width: %d", mapData.width);
		LOG("height: %d", mapData.height);
		LOG("tile width: %d", mapData.tileWidth);
		LOG("tile height: %d", mapData.tileHeight);
		if (mapData.type == MAPTYPE_ORTHOGONAL)
		{
			LOG("orientation: orthogonal");
		}
		else if (mapData.type == MAPTYPE_ISOMETRIC)
		{
			LOG("orientation: isometric");
		}

		ListItem<TileSet*>* tileset;
		tileset = mapData.tilesets.start;
		int tilesetCtr = 0;
		while (tileset != NULL)
		{
			LOG("Tileset %d", tilesetCtr +1);
			LOG("name: %s", tileset->data->name.GetString());
			LOG("first gid: %d", tileset->data->firstgid);
			LOG("margin: %d", tileset->data->margin);
			LOG("spacing: %d", tileset->data->spacing);
			LOG("tile width: %d", tileset->data->tileWidth);
			LOG("tile height: %d", tileset->data->tileHeight);
			LOG("width: %d", tileset->data->texWidth);
			LOG("height: %d", tileset->data->texHeight);

			tileset = tileset->next;
			tilesetCtr++;
		}

		// LOG the info for each loaded layer
		ListItem<MapLayer*>* layer;
		layer = mapData.layers.start;
		int layerCtr = 0;

		while (layer != NULL)
		{
			LOG("Layer %d", layerCtr + 1);
			LOG("name: %s", layer->data->name.GetString());
			LOG("width: %d", layer->data->width);
			LOG("height: %d", layer->data->height);
			
			layerCtr++;
			layer = layer->next;
		}
    }
    mapLoaded = ret;
    return ret;
}

// Load map general properties
bool Map::LoadMap(pugi::xml_node mapFile)
{
	bool ret = true;
	pugi::xml_node map = mapFile.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		// Load map general properties
		mapData.height = map.attribute("height").as_int();
		mapData.width = map.attribute("width").as_int();
		mapData.tileHeight = map.attribute("tileheight").as_int();
		mapData.tileWidth = map.attribute("tilewidth").as_int();

		// Add formula to go from isometric map to world coordinates
		mapData.type = MAPTYPE_UNKNOWN;
		if (strcmp(map.attribute("orientation").as_string(), "isometric") == 0)
		{
			mapData.type = MAPTYPE_ISOMETRIC;
		}
		else if(strcmp(map.attribute("orientation").as_string(), "orthogonal") == 0)
		{
			mapData.type = MAPTYPE_ORTHOGONAL;
		}
		else
		{
			LOG("Error: Map type not known");
		}
	}

	return ret;
}

// Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSets(pugi::xml_node mapFile) {

	bool ret = true;

	pugi::xml_node tileset;
	for (tileset = mapFile.child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();
		if (ret == true) 
			ret = LoadTilesetDetails(tileset, set);
		if (ret == true) 
			ret = LoadTilesetImage(tileset, set);
		mapData.tilesets.add(set);
	}
	return ret;
}

// Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

	// Load Tileset attributes
	set->name.Create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tileWidth = tileset_node.attribute("tilewidth").as_int();
	set->tileHeight = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->tilecount = tileset_node.attribute("tilecount").as_int();

	return ret;
}

// Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		// Load Tileset image
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(tmp.GetString());
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->texWidth = image.attribute("width").as_int();

		if (set->texWidth <= 0) {
			set->texWidth = w;
		}
	}
	set->num_tiles_width = set->texWidth / set->tileWidth;
	return ret;
}

// Implement a function that loads a single layer layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	//Load the attributes
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();

	// Call Load Properties
	LoadProperties(node, layer->properties);
	pugi::xml_node layer_data = node.child("data");

	//Reserve the memory for the tile array
	if (layer_data == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'layer/data' tag.");
		ret = false;
		RELEASE(layer);
	}
	else
	{
		layer->data = new uint[layer->width * layer->height];
		memset(layer->data, 0, layer->width * layer->height);

		int i = 0;
		for (pugi::xml_node tile = layer_data.child("tile"); tile; tile = tile.next_sibling("tile"))
		{
			if (tile.attribute("gid").as_int() == NULL) {
				layer->data[i++] = 0;
			}
			else {
				layer->data[i++] = tile.attribute("gid").as_int();
			}
		}
	}

	//Iterate over all the tiles and assign the values
	pugi::xml_node tile;
	int i = 0;
	for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"))
	{
		layer->data[i] = tile.attribute("gid").as_int();
		i++;
	}

	return ret;
}

// Iterate all layers and load each of them
bool Map::LoadAllLayers(pugi::xml_node mapNode) {
	bool ret = true;
	for (pugi::xml_node layerNode = mapNode.child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		//Load the layer
		MapLayer* mapLayer = new MapLayer();
		ret = LoadLayer(layerNode, mapLayer);

		//add the layer to the map
		mapData.layers.add(mapLayer);
	}

	return ret;
}

// Load a group of properties from a layer and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;
	pugi::xml_node data = node.child("properties");

	if (data != NULL)
	{
		pugi::xml_node prop;

		for (prop = data.child("property"); prop; prop = prop.next_sibling("property"))
		{
			Properties::Property* p = new Properties::Property();

			p->name = prop.attribute("name").as_string();
			p->value = prop.attribute("value").as_int();

			properties.list.add(p);
		}
	}
	return ret;
}

void Map::LoadCol() {
	
	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	int i = 0;

	while (mapLayerItem != NULL) {


		if (mapLayerItem->data->properties.GetProperty("col") == 1) {

			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					// L04: DONE 9: Complete the draw function
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
						//now we always use the firt tileset in the list
						TileSet* tileset = mapData.tilesets.start->data;

						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);
						/*
						app->render->DrawTexture(tileset->texture,
							pos.x,
							pos.y+4,
							&r);
						*/
						collider[i] = app->collisions->AddCollider({ pos.x, pos.y+4, r.w,  r.h }, Collider::Type::GROUND, this);
						i++;
					}

				}
			}
			
		}
		else if (mapLayerItem->data->properties.GetProperty("col") == 2) {


			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					// L04: DONE 9: Complete the draw function
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
						//now we always use the firt tileset in the list
						TileSet* tileset = mapData.tilesets.start->data;

						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);

						/*
						app->render->DrawTexture(tileset->texture,
							pos.x,
							pos.y+4,
							&r);
						*/

						collider[i] = app->collisions->AddCollider({ pos.x, pos.y+4, r.w,  r.h }, Collider::Type::WALL, this);
						i++;
					}

				}
			}
		}
		else if (mapLayerItem->data->properties.GetProperty("col") == 3) {


			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					// L04: DONE 9: Complete the draw function
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
						//now we always use the firt tileset in the list
						TileSet* tileset = mapData.tilesets.start->data;

						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);

						/*
						app->render->DrawTexture(tileset->texture,
							pos.x,
							pos.y+4,
							&r);
						*/

						collider[i] = app->collisions->AddCollider({ pos.x, pos.y + 4, r.w,  r.h }, Collider::Type::DEATH, this);
						i++;
					}

				}
			}
		}
		mapLayerItem = mapLayerItem->next;
	}
}
	
void Map::RemoveCol() {

	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	int i = 0;

	while (mapLayerItem != NULL) {

		for (int x = 0; x < mapLayerItem->data->width; x++)
		{
			for (int y = 0; y < mapLayerItem->data->height; y++)
			{
				// L04: DONE 9: Complete the draw function
				int gid = mapLayerItem->data->Get(x, y);

				if (gid > 0) {

					//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
					//now we always use the firt tileset in the list
					TileSet* tileset = mapData.tilesets.start->data;

					SDL_Rect r = tileset->GetTileRect(gid);
					iPoint pos = MapToWorld(x, y);
					/*
					app->render->DrawTexture(tileset->texture,
						pos.x,
						pos.y+4,
						&r);
					*/
					
					app->collisions->RemoveCollider(collider[i]);
					//collider[i] = app->collisions->AddCollider({ pos.x, pos.y + 4, r.w,  r.h }, Collider::Type::GROUND, this);
					i++;
				}

			}
		}
		mapLayerItem = mapLayerItem->next;
	}

}

/*
bool Map::AddCol(int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < app->; ++i)
	{
		if (spawnQueue[i].type == Box_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}


	}

	return ret;
}
*/