#pragma once

#include "furniture_factory.h"
#include "creature_factory.h"
#include "tile_paths.h"
#include "technology.h"
#include "workshop_array.h"
#include "campaign_builder.h"
#include "custom_item_id.h"
#include "item_factory.h"
#include "map_layouts.h"
#include "biome_info.h"
#include "biome_id.h"
#include "campaign_info.h"
#include "workshop_info.h"
#include "resource_info.h"
#include "layout_mapping_id.h"
#include "layout_mapping.h"
#include "keeper_creature_info.h"
#include "adventurer_creature_info.h"
#include "tile_gas_type.h"
#include "dancing.h"
#include "scripted_help_info.h"
#include "attr_info.h"
#include "buff_id.h"
#include "buff_info.h"
#include "body_material_id.h"
#include "body_material.h"
#include "keybinding_info.h"
#include "world_map_info.h"

class KeyVerifier;
class BuildInfo;
class ExternalEnemy;
class ResourceDistribution;
class EnemyInfo;
class ImmigrantInfo;
class ZLevelInfo;
class BuildingInfo;
struct LayoutGenerator;
struct TileGasInfo;
struct PromotionInfo;
struct BuffInfo;
struct BodyMaterial;

class ContentFactory {
  public:
  optional<string> readData(const GameConfig*, const vector<string>& modNames);
  vector<WorldMapInfo> SERIAL(worldMaps);
  FurnitureFactory SERIAL(furniture);
  map<string, vector<ZLevelInfo>> SERIAL(zLevels);
  vector<ResourceDistribution> SERIAL(resources);
  TilePaths SERIAL(tilePaths);
  map<EnemyId, EnemyInfo> SERIAL(enemies);
  map<string, vector<ExternalEnemy>> SERIAL(externalEnemies);
  ItemFactory SERIAL(itemFactory);
  Technology SERIAL(technology);
  map<string, WorkshopArray> SERIAL(workshopGroups);
  map<string, vector<ImmigrantInfo>> SERIAL(immigrantsData);
  map<string, vector<BuildInfo>> SERIAL(buildInfo);
  VillainsTuple SERIAL(villains);
  GameIntros SERIAL(gameIntros);
  vector<pair<string, KeeperCreatureInfo>> SERIAL(keeperCreatures);
  vector<pair<string, AdventurerCreatureInfo>> SERIAL(adventurerCreatures);
  map<CustomItemId, ItemAttributes> SERIAL(items);
  vector<pair<string, ViewId>> SERIAL(equipmentGroups);
  map<BuildingId, BuildingInfo> SERIAL(buildingInfo);
  MapLayouts SERIAL(mapLayouts);
  map<BiomeId, BiomeInfo> SERIAL(biomeInfo);
  CampaignInfo SERIAL(campaignInfo);
  map<WorkshopType, WorkshopInfo> SERIAL(workshopInfo);
  unordered_map<CollectiveResourceId, ResourceInfo, CustomHash<CollectiveResourceId>> SERIAL(resourceInfo);
  vector<CollectiveResourceId> SERIAL(resourceOrder);
  map<LayoutMappingId, LayoutMapping> SERIAL(layoutMapping);
  map<RandomLayoutId, LayoutGenerator> SERIAL(randomLayouts);
  map<TileGasType, TileGasInfo> SERIAL(tileGasTypes);
  map<string, vector<PromotionInfo>> SERIAL(promotions);
  vector<Dancing::Positions> SERIAL(dancePositions);
  vector<ScriptedHelpInfo> SERIAL(scriptedHelp);
  map<AttrType, AttrInfo> SERIAL(attrInfo);
  vector<AttrType> SERIAL(attrOrder);
  unordered_map<BuffId, BuffInfo, CustomHash<BuffId>> SERIAL(buffs);
  vector<BuffId> SERIAL(buffsModifyingEfficiency);
  unordered_map<BodyMaterialId, BodyMaterial, CustomHash<BodyMaterialId>> SERIAL(bodyMaterials);
  vector<pair<Keybinding, KeybindingInfo>> SERIAL(keybindings);
  void merge(ContentFactory);

  CreatureFactory& getCreatures();
  const CreatureFactory& getCreatures() const;
  optional<WorkshopType> getWorkshopType(FurnitureType) const;

  ContentFactory();
  ~ContentFactory();
  ContentFactory(ContentFactory&&) noexcept;
  ContentFactory& operator = (ContentFactory&&);

  template <class Archive>
  void serialize(Archive& ar, const unsigned int);

  private:
  CreatureFactory SERIAL(creatures);
  optional<string> readCreatureFactory(const GameConfig*, KeyVerifier*);
  optional<string> readFurnitureFactory(const GameConfig*, KeyVerifier*);
  optional<string> readVillainsTuple(const GameConfig*, KeyVerifier*);
  optional<string> readPlayerCreatures(const GameConfig*, KeyVerifier*);
  optional<string> readItems(const GameConfig*, KeyVerifier*);
  optional<string> readBuildingInfo(const GameConfig*, KeyVerifier*);
  optional<string> readWorkshopInfo(const GameConfig*, KeyVerifier*);
  optional<string> readCampaignInfo(const GameConfig*, KeyVerifier*);
  optional<string> readResourceInfo(const GameConfig*, KeyVerifier*);
  optional<string> readZLevels(const GameConfig*, KeyVerifier*);
};

static_assert(std::is_nothrow_move_constructible<ContentFactory>::value, "T should be noexcept MoveConstructible");
