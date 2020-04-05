%top{
#include <stdint.h>
}
%{
    #include "gen/enums.h"
%}
%option case-insensitive
%option noyywrap
%option yylineno
%option nounistd
%option c++
%option yyclass="ai::ScriptTokenizer"
%{
    #include "ScriptLoader.h"
    #include "ScriptTokenizer.h"
    #include "grammar.gen.tab.hpp"
    #include "location.hh"

    static ai::location loc;

    #define YY_USER_ACTION loc.step(); loc.columns(yyleng);

    #undef  YY_DECL
    #define YY_DECL ai::ScriptParser::symbol_type ai::ScriptTokenizer::yylex(ai::ScriptLoader &driver)

    #define yyterminate() return ai::ScriptParser::make_ScriptEnd(loc);

    #define RET_TOKEN(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, loc);
    #define RET_TOKEN_ENUM(token_name, enum_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, ai::enum_name, loc);
    #define RET_STRING(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, yytext, loc);
    #define RET_INT(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, atoi(yytext), loc);

%}


symbolname  [a-zA-Z]+[a-zA-Z-]*
string      \"[^"\r\n]*\"
number      [0-9]+
comment     ;.*
blank   [ \t]+

%%

{comment}
{blank}
"dark-age"    { RET_TOKEN(AgeDarkAge) }
"feudal-age"    { RET_TOKEN(AgeFeudalAge) }
"castle-age"    { RET_TOKEN(AgeCastleAge) }
"imperial-age"    { RET_TOKEN(AgeImperialAge) }
"post-imperial-age"    { RET_TOKEN(AgePostImperialAge) }
"archery-range"    { RET_TOKEN(BuildingArcheryRange) }
"barracks"    { RET_TOKEN(BuildingBarracks) }
"blacksmith"    { RET_TOKEN(BuildingBlacksmith) }
"bombard-tower"    { RET_TOKEN(BuildingBombardTower) }
"castle"    { RET_TOKEN(BuildingCastle) }
"dock"    { RET_TOKEN(BuildingDock) }
"farm"    { RET_TOKEN(BuildingFarm) }
"fish-trap"    { RET_TOKEN(BuildingFishTrap) }
"guard-tower"    { RET_TOKEN(BuildingGuardTower) }
"house"    { RET_TOKEN(BuildingHouse) }
"keep"    { RET_TOKEN(BuildingKeep) }
"lumber-camp"    { RET_TOKEN(BuildingLumberCamp) }
"market"    { RET_TOKEN(BuildingMarket) }
"mill"    { RET_TOKEN(BuildingMill) }
"mining-camp"    { RET_TOKEN(BuildingMiningCamp) }
"monastery"    { RET_TOKEN(BuildingMonastery) }
"outpost"    { RET_TOKEN(BuildingOutpost) }
"siege-workshop"    { RET_TOKEN(BuildingSiegeWorkshop) }
"stable"    { RET_TOKEN(BuildingStable) }
"town-center"    { RET_TOKEN(BuildingTownCenter) }
"university"    { RET_TOKEN(BuildingUniversity) }
"watch-tower"    { RET_TOKEN(BuildingWatchTower) }
"wonder"    { RET_TOKEN(BuildingWonder) }
"watch-tower-line"    { RET_TOKEN(BuildingWatchTowerLine) }
"briton"    { RET_TOKEN(CivBriton) }
"byzantine"    { RET_TOKEN(CivByzantine) }
"celtic"    { RET_TOKEN(CivCeltic) }
"chinese"    { RET_TOKEN(CivChinese) }
"frankish"    { RET_TOKEN(CivFrankish) }
"gothic"    { RET_TOKEN(CivGothic) }
"japanese"    { RET_TOKEN(CivJapanese) }
"mongol"    { RET_TOKEN(CivMongol) }
"persian"    { RET_TOKEN(CivPersian) }
"saracen"    { RET_TOKEN(CivSaracen) }
"teutonic"    { RET_TOKEN(CivTeutonic) }
"turkish"    { RET_TOKEN(CivTurkish) }
"viking"    { RET_TOKEN(CivViking) }
"my-civ"    { RET_TOKEN(CivMyCiv) }
"food"    { RET_TOKEN(CommodityFood) }
"stone"    { RET_TOKEN(CommodityStone) }
"wood"    { RET_TOKEN(CommodityWood) }
"gold"    { RET_TOKEN(CommodityGold) }
"easiest"    { RET_TOKEN(DifficultyLevelEasiest) }
"easy"    { RET_TOKEN(DifficultyLevelEasy) }
"moderate"    { RET_TOKEN(DifficultyLevelModerate) }
"hard"    { RET_TOKEN(DifficultyLevelHard) }
"hardest"    { RET_TOKEN(DifficultyLevelHardest) }
"ability-to-dodge-missiles"    { RET_TOKEN(DifficultyParameterAbilityToDodgeMissiles) }
"ability-to-maintain-distance"    { RET_TOKEN(DifficultyParameterAbilityToMaintainDistance) }
"ally"    { RET_TOKEN(DiplomaticStanceAlly) }
"neutral"    { RET_TOKEN(DiplomaticStanceNeutral) }
"enemy"    { RET_TOKEN(DiplomaticStanceEnemy) }
"tiny"    { RET_TOKEN(MapSizeTypeTiny) }
"small"    { RET_TOKEN(MapSizeTypeSmall) }
"medium"    { RET_TOKEN(MapSizeTypeMedium) }
"normal"    { RET_TOKEN(MapSizeTypeNormal) }
"large"    { RET_TOKEN(MapSizeTypeLarge) }
"giant"    { RET_TOKEN(MapSizeTypeGiant) }
"arabia"    { RET_TOKEN(MapTypeNameArabia) }
"archipelago"    { RET_TOKEN(MapTypeNameArchipelago) }
"baltic"    { RET_TOKEN(MapTypeNameBaltic) }
"black-forest"    { RET_TOKEN(MapTypeNameBlackForest) }
"coastal"    { RET_TOKEN(MapTypeNameCoastal) }
"continental"    { RET_TOKEN(MapTypeNameContinental) }
"crater-lake"    { RET_TOKEN(MapTypeNameCraterLake) }
"fortress"    { RET_TOKEN(MapTypeNameFortress) }
"gold-rush"    { RET_TOKEN(MapTypeNameGoldRush) }
"highland"    { RET_TOKEN(MapTypeNameHighland) }
"islands"    { RET_TOKEN(MapTypeNameIslands) }
"mediterranean"    { RET_TOKEN(MapTypeNameMediterranean) }
"migration"    { RET_TOKEN(MapTypeNameMigration) }
"rivers"    { RET_TOKEN(MapTypeNameRivers) }
"team-islands"    { RET_TOKEN(MapTypeNameTeamIslands) }
"scenario-map"    { RET_TOKEN(MapTypeNameScenarioMap) }
"any-ally"    { RET_TOKEN(PlayerNumberTypeAnyAlly) }
"any-computer"    { RET_TOKEN(PlayerNumberTypeAnyComputer) }
"any-computer-ally"    { RET_TOKEN(PlayerNumberTypeAnyComputerAlly) }
"any-computer-enemy"    { RET_TOKEN(PlayerNumberTypeAnyComputerEnemy) }
"any-computer-neutral"    { RET_TOKEN(PlayerNumberTypeAnyComputerNeutral) }
"any-enemy"    { RET_TOKEN(PlayerNumberTypeAnyEnemy) }
"any-human"    { RET_TOKEN(PlayerNumberTypeAnyHuman) }
"any-human-ally"    { RET_TOKEN(PlayerNumberTypeAnyHumanAlly) }
"any-human-enemy"    { RET_TOKEN(PlayerNumberTypeAnyHumanEnemy) }
"any-human-neutral"    { RET_TOKEN(PlayerNumberTypeAnyHumanNeutral) }
"any-neutral"    { RET_TOKEN(PlayerNumberTypeAnyNeutral) }
"every-ally"    { RET_TOKEN(PlayerNumberTypeEveryAlly) }
"every-computer"    { RET_TOKEN(PlayerNumberTypeEveryComputer) }
"every-enemy"    { RET_TOKEN(PlayerNumberTypeEveryEnemy) }
"every-human"    { RET_TOKEN(PlayerNumberTypeEveryHuman) }
"every-neutral"    { RET_TOKEN(PlayerNumberTypeEveryNeutral) }
"my-player-number"    { RET_TOKEN(PlayerNumberTypeMyPlayerNumber) }
"less-than"    { RET_TOKEN(RelOpLessThan) }
"less-or-equal"    { RET_TOKEN(RelOpLessOrEqual) }
"greater-than"    { RET_TOKEN(RelOpGreaterThan) }
"greater-or-equal"    { RET_TOKEN(RelOpGreaterOrEqual) }
"equal"    { RET_TOKEN(RelOpEqual) }
"not-equal"    { RET_TOKEN(RelOpNotEqual) }
"ri-arbalest"    { RET_TOKEN(ResearchItemRiArbalest) }
"ri-crossbow"    { RET_TOKEN(ResearchItemRiCrossbow) }
"ri-elite-skirmisher"    { RET_TOKEN(ResearchItemRiEliteSkirmisher) }
"ri-hand-cannon"    { RET_TOKEN(ResearchItemRiHandCannon) }
"ri-heavy-cavalry-archer"    { RET_TOKEN(ResearchItemRiHeavyCavalryArcher) }
"ri-champion"    { RET_TOKEN(ResearchItemRiChampion) }
"ri-elite-eagle-warrior"    { RET_TOKEN(ResearchItemRiEliteEagleWarrior) }
"ri-halberdier"    { RET_TOKEN(ResearchItemRiHalberdier) }
"ri-long-swordsman"    { RET_TOKEN(ResearchItemRiLongSwordsman) }
"ri-man-at-arms"    { RET_TOKEN(ResearchItemRiManAtArms) }
"ri-parthian-tactics"    { RET_TOKEN(ResearchItemRiParthianTactics) }
"ri-pikeman"    { RET_TOKEN(ResearchItemRiPikeman) }
"ri-squires"    { RET_TOKEN(ResearchItemRiSquires) }
"ri-thumb-ring"    { RET_TOKEN(ResearchItemRiThumbRing) }
"ri-tracking"    { RET_TOKEN(ResearchItemRiTracking) }
"ri-two-handed-swordsman"    { RET_TOKEN(ResearchItemRiTwoHandedSwordsman) }
"ri-blast-furnace"    { RET_TOKEN(ResearchItemRiBlastFurnace) }
"ri-bodkin-arrow"    { RET_TOKEN(ResearchItemRiBodkinArrow) }
"ri-bracer"    { RET_TOKEN(ResearchItemRiBracer) }
"ri-chain-barding"    { RET_TOKEN(ResearchItemRiChainBarding) }
"ri-chain-mail"    { RET_TOKEN(ResearchItemRiChainMail) }
"ri-fletching"    { RET_TOKEN(ResearchItemRiFletching) }
"ri-forging"    { RET_TOKEN(ResearchItemRiForging) }
"ri-iron-casting"    { RET_TOKEN(ResearchItemRiIronCasting) }
"ri-leather-archer-armor"    { RET_TOKEN(ResearchItemRiLeatherArcherArmor) }
"ri-padded-archer-armor"    { RET_TOKEN(ResearchItemRiPaddedArcherArmor) }
"ri-plate-barding"    { RET_TOKEN(ResearchItemRiPlateBarding) }
"ri-plate-mail"    { RET_TOKEN(ResearchItemRiPlateMail) }
"ri-ring-archer-armor"    { RET_TOKEN(ResearchItemRiRingArcherArmor) }
"ri-scale-barding"    { RET_TOKEN(ResearchItemRiScaleBarding) }
"ri-scale-mail"    { RET_TOKEN(ResearchItemRiScaleMail) }
"ri-conscription"    { RET_TOKEN(ResearchItemRiConscription) }
"ri-hoardings"    { RET_TOKEN(ResearchItemRiHoardings) }
"ri-sappers"    { RET_TOKEN(ResearchItemRiSappers) }
"ri-elite-berserk"    { RET_TOKEN(ResearchItemRiEliteBerserk) }
"ri-elite-cataphract"    { RET_TOKEN(ResearchItemRiEliteCataphract) }
"ri-elite-chu-ko-nu"    { RET_TOKEN(ResearchItemRiEliteChuKoNu) }
"ri-elite-huskarl"    { RET_TOKEN(ResearchItemRiEliteHuskarl) }
"ri-elite-janissary"    { RET_TOKEN(ResearchItemRiEliteJanissary) }
"ri-elite-longbowman"    { RET_TOKEN(ResearchItemRiEliteLongbowman) }
"ri-elite-mameluke"    { RET_TOKEN(ResearchItemRiEliteMameluke) }
"ri-elite-mangudai"    { RET_TOKEN(ResearchItemRiEliteMangudai) }
"ri-elite-samurai"    { RET_TOKEN(ResearchItemRiEliteSamurai) }
"ri-elite-teutonic-knight"    { RET_TOKEN(ResearchItemRiEliteTeutonicKnight) }
"ri-elite-throwing-axeman"    { RET_TOKEN(ResearchItemRiEliteThrowingAxeman) }
"ri-elite-war-elephant"    { RET_TOKEN(ResearchItemRiEliteWarElephant) }
"ri-elite-woad-raider"    { RET_TOKEN(ResearchItemRiEliteWoadRaider) }
"ri-my-unique-elite-unit"    { RET_TOKEN(ResearchItemRiMyUniqueEliteUnit) }
"ri-my-unique-research"    { RET_TOKEN(ResearchItemRiMyUniqueResearch) }
"ri-cannon-galleon"    { RET_TOKEN(ResearchItemRiCannonGalleon) }
"ri-careening"    { RET_TOKEN(ResearchItemRiCareening) }
"ri-deck-guns"    { RET_TOKEN(ResearchItemRiDeckGuns) }
"ri-dry-dock"    { RET_TOKEN(ResearchItemRiDryDock) }
"ri-elite-longboat"    { RET_TOKEN(ResearchItemRiEliteLongboat) }
"ri-fast-fire-ship"    { RET_TOKEN(ResearchItemRiFastFireShip) }
"ri-galleon"    { RET_TOKEN(ResearchItemRiGalleon) }
"ri-heavy-demolition-ship"    { RET_TOKEN(ResearchItemRiHeavyDemolitionShip) }
"ri-shipwright"    { RET_TOKEN(ResearchItemRiShipwright) }
"ri-war-galley"    { RET_TOKEN(ResearchItemRiWarGalley) }
"ri-bow-saw"    { RET_TOKEN(ResearchItemRiBowSaw) }
"ri-double-bit-axe"    { RET_TOKEN(ResearchItemRiDoubleBitAxe) }
"ri-two-man-saw"    { RET_TOKEN(ResearchItemRiTwoManSaw) }
"ri-banking"    { RET_TOKEN(ResearchItemRiBanking) }
"ri-caravan"    { RET_TOKEN(ResearchItemRiCaravan) }
"ri-cartography"    { RET_TOKEN(ResearchItemRiCartography) }
"ri-coinage"    { RET_TOKEN(ResearchItemRiCoinage) }
"ri-guilds"    { RET_TOKEN(ResearchItemRiGuilds) }
"ri-crop-rotation"    { RET_TOKEN(ResearchItemRiCropRotation) }
"ri-heavy-plow"    { RET_TOKEN(ResearchItemRiHeavyPlow) }
"ri-horse-collar"    { RET_TOKEN(ResearchItemRiHorseCollar) }
"ri-gold-mining"    { RET_TOKEN(ResearchItemRiGoldMining) }
"ri-gold-shaft-mining"    { RET_TOKEN(ResearchItemRiGoldShaftMining) }
"ri-stone-mining"    { RET_TOKEN(ResearchItemRiStoneMining) }
"ri-stone-shaft-mining"    { RET_TOKEN(ResearchItemRiStoneShaftMining) }
"ri-atonement"    { RET_TOKEN(ResearchItemRiAtonement) }
"ri-block-printing"    { RET_TOKEN(ResearchItemRiBlockPrinting) }
"ri-faith"    { RET_TOKEN(ResearchItemRiFaith) }
"ri-fervor"    { RET_TOKEN(ResearchItemRiFervor) }
"ri-herbal-medicine"    { RET_TOKEN(ResearchItemRiHerbalMedicine) }
"ri-heresy"    { RET_TOKEN(ResearchItemRiHeresy) }
"ri-illumination"    { RET_TOKEN(ResearchItemRiIllumination) }
"ri-redemption"    { RET_TOKEN(ResearchItemRiRedemption) }
"ri-sanctity"    { RET_TOKEN(ResearchItemRiSanctity) }
"ri-theocracy"    { RET_TOKEN(ResearchItemRiTheocracy) }
"ri-bombard-cannon"    { RET_TOKEN(ResearchItemRiBombardCannon) }
"ri-capped-ram"    { RET_TOKEN(ResearchItemRiCappedRam) }
"ri-heavy-scorpion"    { RET_TOKEN(ResearchItemRiHeavyScorpion) }
"ri-onager"    { RET_TOKEN(ResearchItemRiOnager) }
"ri-scorpion"    { RET_TOKEN(ResearchItemRiScorpion) }
"ri-siege-onager"    { RET_TOKEN(ResearchItemRiSiegeOnager) }
"ri-siege-ram"    { RET_TOKEN(ResearchItemRiSiegeRam) }
"ri-bloodlines"    { RET_TOKEN(ResearchItemRiBloodlines) }
"ri-cavalier"    { RET_TOKEN(ResearchItemRiCavalier) }
"ri-heavy-camel"    { RET_TOKEN(ResearchItemRiHeavyCamel) }
"ri-husbandry"    { RET_TOKEN(ResearchItemRiHusbandry) }
"ri-hussar"    { RET_TOKEN(ResearchItemRiHussar) }
"ri-light-cavalry"    { RET_TOKEN(ResearchItemRiLightCavalry) }
"ri-paladin"    { RET_TOKEN(ResearchItemRiPaladin) }
"ri-hand-cart"    { RET_TOKEN(ResearchItemRiHandCart) }
"ri-loom"    { RET_TOKEN(ResearchItemRiLoom) }
"ri-town-patrol"    { RET_TOKEN(ResearchItemRiTownPatrol) }
"ri-town-watch"    { RET_TOKEN(ResearchItemRiTownWatch) }
"ri-wheel-barrow"    { RET_TOKEN(ResearchItemRiWheelBarrow) }
"ri-architecture"    { RET_TOKEN(ResearchItemRiArchitecture) }
"ri-ballistics"    { RET_TOKEN(ResearchItemRiBallistics) }
"ri-bombard-tower"    { RET_TOKEN(ResearchItemRiBombardTower) }
"ri-chemistry"    { RET_TOKEN(ResearchItemRiChemistry) }
"ri-fortified-wall"    { RET_TOKEN(ResearchItemRiFortifiedWall) }
"ri-guard-tower"    { RET_TOKEN(ResearchItemRiGuardTower) }
"ri-heated-shot"    { RET_TOKEN(ResearchItemRiHeatedShot) }
"ri-keep"    { RET_TOKEN(ResearchItemRiKeep) }
"ri-masonry"    { RET_TOKEN(ResearchItemRiMasonry) }
"ri-murder-holes"    { RET_TOKEN(ResearchItemRiMurderHoles) }
"ri-siege-engineers"    { RET_TOKEN(ResearchItemRiSiegeEngineers) }
"ri-stonecutting"    { RET_TOKEN(ResearchItemRiStonecutting) }
"my-unique-unit-upgrade"    { RET_TOKEN(ResearchItemMyUniqueUnitUpgrade) }
"my-unique-research"    { RET_TOKEN(ResearchItemMyUniqueResearch) }
"low-resources"    { RET_TOKEN(StartingResourcesTypeLowResources) }
"medium-resources"    { RET_TOKEN(StartingResourcesTypeMediumResources) }
"high-resources"    { RET_TOKEN(StartingResourcesTypeHighResources) }
"sn-percent-civilian-explorers"    { RET_TOKEN(StrategicNumberNameSnPercentCivilianExplorers) }
"sn-percent-civilian-builders"    { RET_TOKEN(StrategicNumberNameSnPercentCivilianBuilders) }
"sn-percent-civilian-gatherers"    { RET_TOKEN(StrategicNumberNameSnPercentCivilianGatherers) }
"sn-cap-civilian-explorers"    { RET_TOKEN(StrategicNumberNameSnCapCivilianExplorers) }
"sn-cap-civilian-builders"    { RET_TOKEN(StrategicNumberNameSnCapCivilianBuilders) }
"sn-cap-civilian-gatherers"    { RET_TOKEN(StrategicNumberNameSnCapCivilianGatherers) }
"sn-minimum-attack-group-size"    { RET_TOKEN(StrategicNumberNameSnMinimumAttackGroupSize) }
"sn-total-number-explorers"    { RET_TOKEN(StrategicNumberNameSnTotalNumberExplorers) }
"sn-percent-enemy-sighted-response"    { RET_TOKEN(StrategicNumberNameSnPercentEnemySightedResponse) }
"sn-enemy-sighted-response-distance"    { RET_TOKEN(StrategicNumberNameSnEnemySightedResponseDistance) }
"sn-sentry-distance"    { RET_TOKEN(StrategicNumberNameSnSentryDistance) }
"sn-relic-return-distance"    { RET_TOKEN(StrategicNumberNameSnRelicReturnDistance) }
"sn-minimum-defend-group-size"    { RET_TOKEN(StrategicNumberNameSnMinimumDefendGroupSize) }
"sn-maximum-attack-group-size"    { RET_TOKEN(StrategicNumberNameSnMaximumAttackGroupSize) }
"sn-maximum-defend-group-size"    { RET_TOKEN(StrategicNumberNameSnMaximumDefendGroupSize) }
"sn-minimum-peace-like-level"    { RET_TOKEN(StrategicNumberNameSnMinimumPeaceLikeLevel) }
"sn-percent-exploration-required"    { RET_TOKEN(StrategicNumberNameSnPercentExplorationRequired) }
"sn-zero-priority-distance"    { RET_TOKEN(StrategicNumberNameSnZeroPriorityDistance) }
"sn-minimum-civilian-explorers"    { RET_TOKEN(StrategicNumberNameSnMinimumCivilianExplorers) }
"sn-number-attack-groups"    { RET_TOKEN(StrategicNumberNameSnNumberAttackGroups) }
"sn-number-defend-groups"    { RET_TOKEN(StrategicNumberNameSnNumberDefendGroups) }
"sn-attack-group-gather-spacing"    { RET_TOKEN(StrategicNumberNameSnAttackGroupGatherSpacing) }
"sn-number-explore-groups"    { RET_TOKEN(StrategicNumberNameSnNumberExploreGroups) }
"sn-minimum-explore-group-size"    { RET_TOKEN(StrategicNumberNameSnMinimumExploreGroupSize) }
"sn-maximum-explore-group-size"    { RET_TOKEN(StrategicNumberNameSnMaximumExploreGroupSize) }
"sn-gold-defend-priority"    { RET_TOKEN(StrategicNumberNameSnGoldDefendPriority) }
"sn-stone-defend-priority"    { RET_TOKEN(StrategicNumberNameSnStoneDefendPriority) }
"sn-forage-defend-priority"    { RET_TOKEN(StrategicNumberNameSnForageDefendPriority) }
"sn-relic-defend-priority"    { RET_TOKEN(StrategicNumberNameSnRelicDefendPriority) }
"sn-town-defend-priority"    { RET_TOKEN(StrategicNumberNameSnTownDefendPriority) }
"sn-defense-distance"    { RET_TOKEN(StrategicNumberNameSnDefenseDistance) }
"sn-number-boat-attack-groups"    { RET_TOKEN(StrategicNumberNameSnNumberBoatAttackGroups) }
"sn-minimum-boat-attack-group-size"    { RET_TOKEN(StrategicNumberNameSnMinimumBoatAttackGroupSize) }
"sn-maximum-boat-attack-group-size"    { RET_TOKEN(StrategicNumberNameSnMaximumBoatAttackGroupSize) }
"sn-number-boat-explore-groups"    { RET_TOKEN(StrategicNumberNameSnNumberBoatExploreGroups) }
"sn-minimum-boat-explore-group-size"    { RET_TOKEN(StrategicNumberNameSnMinimumBoatExploreGroupSize) }
"sn-maximum-boat-explore-group-size"    { RET_TOKEN(StrategicNumberNameSnMaximumBoatExploreGroupSize) }
"sn-number-boat-defend-groups"    { RET_TOKEN(StrategicNumberNameSnNumberBoatDefendGroups) }
"sn-minimum-boat-defend-group-size"    { RET_TOKEN(StrategicNumberNameSnMinimumBoatDefendGroupSize) }
"sn-maximum-boat-defend-group-size"    { RET_TOKEN(StrategicNumberNameSnMaximumBoatDefendGroupSize) }
"sn-dock-defend-priority"    { RET_TOKEN(StrategicNumberNameSnDockDefendPriority) }
"sn-sentry-distance-variation"    { RET_TOKEN(StrategicNumberNameSnSentryDistanceVariation) }
"sn-minimum-town-size"    { RET_TOKEN(StrategicNumberNameSnMinimumTownSize) }
"sn-maximum-town-size"    { RET_TOKEN(StrategicNumberNameSnMaximumTownSize) }
"sn-group-commander-selection-method"    { RET_TOKEN(StrategicNumberNameSnGroupCommanderSelectionMethod) }
"sn-consecutive-idle-unit-limit"    { RET_TOKEN(StrategicNumberNameSnConsecutiveIdleUnitLimit) }
"sn-target-evaluation-distance"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationDistance) }
"sn-target-evaluation-hitpoints"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationHitpoints) }
"sn-target-evaluation-damage-capability"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationDamageCapability) }
"sn-target-evaluation-kills"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationKills) }
"sn-target-evaluation-ally-proximity"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationAllyProximity) }
"sn-target-evaluation-rof"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationRof) }
"sn-target-evaluation-randomness"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationRandomness) }
"sn-camp-max-distance"    { RET_TOKEN(StrategicNumberNameSnCampMaxDistance) }
"sn-mill-max-distance"    { RET_TOKEN(StrategicNumberNameSnMillMaxDistance) }
"sn-target-evaluation-attack-attempts"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationAttackAttempts) }
"sn-target-evaluation-range"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationRange) }
"sn-defend-overlap-distance"    { RET_TOKEN(StrategicNumberNameSnDefendOverlapDistance) }
"sn-scale-minimum-attack-group-size"    { RET_TOKEN(StrategicNumberNameSnScaleMinimumAttackGroupSize) }
"sn-scale-maximum-attack-group-size"    { RET_TOKEN(StrategicNumberNameSnScaleMaximumAttackGroupSize) }
"sn-attack-group-size-randomness"    { RET_TOKEN(StrategicNumberNameSnAttackGroupSizeRandomness) }
"sn-scaling-frequency"    { RET_TOKEN(StrategicNumberNameSnScalingFrequency) }
"sn-maximum-gaia-attack-response"    { RET_TOKEN(StrategicNumberNameSnMaximumGaiaAttackResponse) }
"sn-build-frequency"    { RET_TOKEN(StrategicNumberNameSnBuildFrequency) }
"sn-attack-separation-time-randomness"    { RET_TOKEN(StrategicNumberNameSnAttackSeparationTimeRandomness) }
"sn-attack-intelligence"    { RET_TOKEN(StrategicNumberNameSnAttackIntelligence) }
"sn-initial-attack-delay"    { RET_TOKEN(StrategicNumberNameSnInitialAttackDelay) }
"sn-save-scenario-information"    { RET_TOKEN(StrategicNumberNameSnSaveScenarioInformation) }
"sn-special-attack-type1"    { RET_TOKEN(StrategicNumberNameSnSpecialAttackType1) }
"sn-special-attack-influence1"    { RET_TOKEN(StrategicNumberNameSnSpecialAttackInfluence1) }
"sn-minimum-water-body-size-for-dock"    { RET_TOKEN(StrategicNumberNameSnMinimumWaterBodySizeForDock) }
"sn-number-build-attempts-before-skip"    { RET_TOKEN(StrategicNumberNameSnNumberBuildAttemptsBeforeSkip) }
"sn-max-skips-per-attempt"    { RET_TOKEN(StrategicNumberNameSnMaxSkipsPerAttempt) }
"sn-food-gatherer-percentage"    { RET_TOKEN(StrategicNumberNameSnFoodGathererPercentage) }
"sn-gold-gatherer-percentage"    { RET_TOKEN(StrategicNumberNameSnGoldGathererPercentage) }
"sn-stone-gatherer-percentage"    { RET_TOKEN(StrategicNumberNameSnStoneGathererPercentage) }
"sn-wood-gatherer-percentage"    { RET_TOKEN(StrategicNumberNameSnWoodGathererPercentage) }
"sn-target-evaluation-continent"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationContinent) }
"sn-target-evaluation-siege-weapon"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationSiegeWeapon) }
"sn-group-leader-defense-distance"    { RET_TOKEN(StrategicNumberNameSnGroupLeaderDefenseDistance) }
"sn-initial-attack-delay-type"    { RET_TOKEN(StrategicNumberNameSnInitialAttackDelayType) }
"sn-blot-exploration-map"    { RET_TOKEN(StrategicNumberNameSnBlotExplorationMap) }
"sn-blot-size"    { RET_TOKEN(StrategicNumberNameSnBlotSize) }
"sn-intelligent-gathering"    { RET_TOKEN(StrategicNumberNameSnIntelligentGathering) }
"sn-task-ungrouped-soldiers"    { RET_TOKEN(StrategicNumberNameSnTaskUngroupedSoldiers) }
"sn-target-evaluation-boat"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationBoat) }
"sn-number-enemy-objects-required"    { RET_TOKEN(StrategicNumberNameSnNumberEnemyObjectsRequired) }
"sn-number-max-skip-cycles"    { RET_TOKEN(StrategicNumberNameSnNumberMaxSkipCycles) }
"sn-retask-gather-amount"    { RET_TOKEN(StrategicNumberNameSnRetaskGatherAmount) }
"sn-max-retask-gather-amount"    { RET_TOKEN(StrategicNumberNameSnMaxRetaskGatherAmount) }
"sn-max-build-plan-gatherer-percentage"    { RET_TOKEN(StrategicNumberNameSnMaxBuildPlanGathererPercentage) }
"sn-food-dropsite-distance"    { RET_TOKEN(StrategicNumberNameSnFoodDropsiteDistance) }
"sn-wood-dropsite-distance"    { RET_TOKEN(StrategicNumberNameSnWoodDropsiteDistance) }
"sn-stone-dropsite-distance"    { RET_TOKEN(StrategicNumberNameSnStoneDropsiteDistance) }
"sn-gold-dropsite-distance"    { RET_TOKEN(StrategicNumberNameSnGoldDropsiteDistance) }
"sn-initial-exploration-required"    { RET_TOKEN(StrategicNumberNameSnInitialExplorationRequired) }
"sn-random-placement-factor"    { RET_TOKEN(StrategicNumberNameSnRandomPlacementFactor) }
"sn-required-forest-tiles"    { RET_TOKEN(StrategicNumberNameSnRequiredForestTiles) }
"sn-attack-diplomacy-impact"    { RET_TOKEN(StrategicNumberNameSnAttackDiplomacyImpact) }
"sn-percent-half-exploration"    { RET_TOKEN(StrategicNumberNameSnPercentHalfExploration) }
"sn-target-evaluation-time-kill-ratio"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationTimeKillRatio) }
"sn-target-evaluation-in-progress"    { RET_TOKEN(StrategicNumberNameSnTargetEvaluationInProgress) }
"sn-attack-winning-player"    { RET_TOKEN(StrategicNumberNameSnAttackWinningPlayer) }
"sn-coop-share-information"    { RET_TOKEN(StrategicNumberNameSnCoopShareInformation) }
"sn-attack-winning-player-factor"    { RET_TOKEN(StrategicNumberNameSnAttackWinningPlayerFactor) }
"sn-coop-share-attacking"    { RET_TOKEN(StrategicNumberNameSnCoopShareAttacking) }
"sn-coop-share-attacking-interval"    { RET_TOKEN(StrategicNumberNameSnCoopShareAttackingInterval) }
"sn-percentage-explore-exterminators"    { RET_TOKEN(StrategicNumberNameSnPercentageExploreExterminators) }
"sn-track-player-history"    { RET_TOKEN(StrategicNumberNameSnTrackPlayerHistory) }
"sn-minimum-dropsite-buffer"    { RET_TOKEN(StrategicNumberNameSnMinimumDropsiteBuffer) }
"sn-use-by-type-max-gathering"    { RET_TOKEN(StrategicNumberNameSnUseByTypeMaxGathering) }
"sn-minimum-boar-hunt-group-size"    { RET_TOKEN(StrategicNumberNameSnMinimumBoarHuntGroupSize) }
"sn-minimum-amount-for-trading"    { RET_TOKEN(StrategicNumberNameSnMinimumAmountForTrading) }
"sn-easiest-reaction-percentage"    { RET_TOKEN(StrategicNumberNameSnEasiestReactionPercentage) }
"sn-easier-reaction-percentage"    { RET_TOKEN(StrategicNumberNameSnEasierReactionPercentage) }
"sn-hits-before-alliance-change"    { RET_TOKEN(StrategicNumberNameSnHitsBeforeAllianceChange) }
"sn-allow-civilian-defense"    { RET_TOKEN(StrategicNumberNameSnAllowCivilianDefense) }
"sn-number-forward-builders"    { RET_TOKEN(StrategicNumberNameSnNumberForwardBuilders) }
"sn-percent-attack-soldiers"    { RET_TOKEN(StrategicNumberNameSnPercentAttackSoldiers) }
"sn-percent-attack-boats"    { RET_TOKEN(StrategicNumberNameSnPercentAttackBoats) }
"sn-do-not-scale-for-difficulty-level"    { RET_TOKEN(StrategicNumberNameSnDoNotScaleForDifficultyLevel) }
"sn-group-form-distance"    { RET_TOKEN(StrategicNumberNameSnGroupFormDistance) }
"sn-ignore-attack-group-under-attack"    { RET_TOKEN(StrategicNumberNameSnIgnoreAttackGroupUnderAttack) }
"sn-gather-defense-units"    { RET_TOKEN(StrategicNumberNameSnGatherDefenseUnits) }
"sn-maximum-wood-drop-distance"    { RET_TOKEN(StrategicNumberNameSnMaximumWoodDropDistance) }
"sn-maximum-food-drop-distance"    { RET_TOKEN(StrategicNumberNameSnMaximumFoodDropDistance) }
"sn-maximum-hunt-drop-distance"    { RET_TOKEN(StrategicNumberNameSnMaximumHuntDropDistance) }
"sn-maximum-fish-boat-drop-distance"    { RET_TOKEN(StrategicNumberNameSnMaximumFishBoatDropDistance) }
"sn-maximum-gold-drop-distance"    { RET_TOKEN(StrategicNumberNameSnMaximumGoldDropDistance) }
"sn-maximum-stone-drop-distance"    { RET_TOKEN(StrategicNumberNameSnMaximumStoneDropDistance) }
"sn-gather-idle-soldiers-at-center"    { RET_TOKEN(StrategicNumberNameSnGatherIdleSoldiersAtCenter) }
"sn-garrison-rams"    { RET_TOKEN(StrategicNumberNameSnGarrisonRams) }
"arbalest"    { RET_TOKEN(UnitArbalest) }
"archer"    { RET_TOKEN(UnitArcher) }
"cavalry-archer"    { RET_TOKEN(UnitCavalryArcher) }
"crossbowman"    { RET_TOKEN(UnitCrossbowman) }
"elite-skirmisher"    { RET_TOKEN(UnitEliteSkirmisher) }
"hand-cannoneer"    { RET_TOKEN(UnitHandCannoneer) }
"heavy-cavalry-archer"    { RET_TOKEN(UnitHeavyCavalryArcher) }
"skirmisher"    { RET_TOKEN(UnitSkirmisher) }
"champion"    { RET_TOKEN(UnitChampion) }
"eagle-warrior"    { RET_TOKEN(UnitEagleWarrior) }
"elite-eagle-warrior"    { RET_TOKEN(UnitEliteEagleWarrior) }
"halberdier"    { RET_TOKEN(UnitHalberdier) }
"long-swordsman"    { RET_TOKEN(UnitLongSwordsman) }
"man-at-arms"    { RET_TOKEN(UnitManAtArms) }
"militiaman"    { RET_TOKEN(UnitMilitiaman) }
"pikeman"    { RET_TOKEN(UnitPikeman) }
"spearman"    { RET_TOKEN(UnitSpearman) }
"two-handed-swordsman"    { RET_TOKEN(UnitTwoHandedSwordsman) }
"berserk"    { RET_TOKEN(UnitBerserk) }
"cataphract"    { RET_TOKEN(UnitCataphract) }
"chu-ko-nu"    { RET_TOKEN(UnitChuKoNu) }
"conquistador"    { RET_TOKEN(UnitConquistador) }
"elite-berserk"    { RET_TOKEN(UnitEliteBerserk) }
"elite-cataphract"    { RET_TOKEN(UnitEliteCataphract) }
"elite-chu-ko-nu"    { RET_TOKEN(UnitEliteChuKoNu) }
"elite-conquistador"    { RET_TOKEN(UnitEliteConquistador) }
"elite-huskarl"    { RET_TOKEN(UnitEliteHuskarl) }
"elite-jaguar-warrior"    { RET_TOKEN(UnitEliteJaguarWarrior) }
"elite-janissary"    { RET_TOKEN(UnitEliteJanissary) }
"elite-longbowman"    { RET_TOKEN(UnitEliteLongbowman) }
"elite-mameluke"    { RET_TOKEN(UnitEliteMameluke) }
"elite-mangudai"    { RET_TOKEN(UnitEliteMangudai) }
"elite-plumed-archer"    { RET_TOKEN(UnitElitePlumedArcher) }
"elite-samurai"    { RET_TOKEN(UnitEliteSamurai) }
"elite-tarkan"    { RET_TOKEN(UnitEliteTarkan) }
"elite-teutonic-knight"    { RET_TOKEN(UnitEliteTeutonicKnight) }
"elite-throwing-axeman"    { RET_TOKEN(UnitEliteThrowingAxeman) }
"elite-war-elephant"    { RET_TOKEN(UnitEliteWarElephant) }
"elite-war-wagon"    { RET_TOKEN(UnitEliteWarWagon) }
"elite-woad-raider"    { RET_TOKEN(UnitEliteWoadRaider) }
"huskarl"    { RET_TOKEN(UnitHuskarl) }
"jaguar-warrior"    { RET_TOKEN(UnitJaguarWarrior) }
"janissary"    { RET_TOKEN(UnitJanissary) }
"longbowman"    { RET_TOKEN(UnitLongbowman) }
"mameluke"    { RET_TOKEN(UnitMameluke) }
"mangudai"    { RET_TOKEN(UnitMangudai) }
"petard"    { RET_TOKEN(UnitPetard) }
"plumed-archer"    { RET_TOKEN(UnitPlumedArcher) }
"samurai"    { RET_TOKEN(UnitSamurai) }
"tarkan"    { RET_TOKEN(UnitTarkan) }
"teutonic-knight"    { RET_TOKEN(UnitTeutonicKnight) }
"throwing-axeman"    { RET_TOKEN(UnitThrowingAxeman) }
"trebuchet"    { RET_TOKEN(UnitTrebuchet) }
"war-elephant"    { RET_TOKEN(UnitWarElephant) }
"war-wagon"    { RET_TOKEN(UnitWarWagon) }
"woad-raider"    { RET_TOKEN(UnitWoadRaider) }
"cannon-galleon"    { RET_TOKEN(UnitCannonGalleon) }
"demolition-ship"    { RET_TOKEN(UnitDemolitionShip) }
"elite-cannon-galleon"    { RET_TOKEN(UnitEliteCannonGalleon) }
"elite-longboat"    { RET_TOKEN(UnitEliteLongboat) }
"elite-turtle-ship"    { RET_TOKEN(UnitEliteTurtleShip) }
"fast-fire-ship"    { RET_TOKEN(UnitFastFireShip) }
"fire-ship"    { RET_TOKEN(UnitFireShip) }
"fishing-ship"    { RET_TOKEN(UnitFishingShip) }
"galleon"    { RET_TOKEN(UnitGalleon) }
"galley"    { RET_TOKEN(UnitGalley) }
"heavy-demolition-ship"    { RET_TOKEN(UnitHeavyDemolitionShip) }
"longboat"    { RET_TOKEN(UnitLongboat) }
"trade-cog"    { RET_TOKEN(UnitTradeCog) }
"transport-ship"    { RET_TOKEN(UnitTransportShip) }
"turtle-ship"    { RET_TOKEN(UnitTurtleShip) }
"war-galley"    { RET_TOKEN(UnitWarGalley) }
"trade-cart"    { RET_TOKEN(UnitTradeCart) }
"missionary"    { RET_TOKEN(UnitMissionary) }
"monk"    { RET_TOKEN(UnitMonk) }
"battering-ram"    { RET_TOKEN(UnitBatteringRam) }
"bombard-cannon"    { RET_TOKEN(UnitBombardCannon) }
"capped-ram"    { RET_TOKEN(UnitCappedRam) }
"heavy-scorpion"    { RET_TOKEN(UnitHeavyScorpion) }
"mangonel"    { RET_TOKEN(UnitMangonel) }
"onager"    { RET_TOKEN(UnitOnager) }
"scorpion"    { RET_TOKEN(UnitScorpion) }
"siege-onager"    { RET_TOKEN(UnitSiegeOnager) }
"siege-ram"    { RET_TOKEN(UnitSiegeRam) }
"camel"    { RET_TOKEN(UnitCamel) }
"cavalier"    { RET_TOKEN(UnitCavalier) }
"heavy-camel"    { RET_TOKEN(UnitHeavyCamel) }
"hussar"    { RET_TOKEN(UnitHussar) }
"knight"    { RET_TOKEN(UnitKnight) }
"light-cavalry"    { RET_TOKEN(UnitLightCavalry) }
"paladin"    { RET_TOKEN(UnitPaladin) }
"scout-cavalry"    { RET_TOKEN(UnitScoutCavalry) }
"villager"    { RET_TOKEN(UnitVillager) }
"archer-line"    { RET_TOKEN(UnitArcherLine) }
"cavalry-archer-line"    { RET_TOKEN(UnitCavalryArcherLine) }
"skirmisher-line"    { RET_TOKEN(UnitSkirmisherLine) }
"eagle-warrior-line"    { RET_TOKEN(UnitEagleWarriorLine) }
"militiaman-line"    { RET_TOKEN(UnitMilitiamanLine) }
"spearman-line"    { RET_TOKEN(UnitSpearmanLine) }
"berserk-line"    { RET_TOKEN(UnitBerserkLine) }
"cataphract-line"    { RET_TOKEN(UnitCataphractLine) }
"chu-ko-nu-line"    { RET_TOKEN(UnitChuKoNuLine) }
"conquistador-line"    { RET_TOKEN(UnitConquistadorLine) }
"huskarl-line"    { RET_TOKEN(UnitHuskarlLine) }
"jaguar-warrior-line"    { RET_TOKEN(UnitJaguarWarriorLine) }
"janissary-line"    { RET_TOKEN(UnitJanissaryLine) }
"longbowman-line"    { RET_TOKEN(UnitLongbowmanLine) }
"mameluke-line"    { RET_TOKEN(UnitMamelukeLine) }
"mangudai-line"    { RET_TOKEN(UnitMangudaiLine) }
"plumed-archer-line"    { RET_TOKEN(UnitPlumedArcherLine) }
"samurai-line"    { RET_TOKEN(UnitSamuraiLine) }
"tarkan-line"    { RET_TOKEN(UnitTarkanLine) }
"teutonic-knight-line"    { RET_TOKEN(UnitTeutonicKnightLine) }
"throwing-axeman-line"    { RET_TOKEN(UnitThrowingAxemanLine) }
"war-elephant-line"    { RET_TOKEN(UnitWarElephantLine) }
"war-wagon-line"    { RET_TOKEN(UnitWarWagonLine) }
"woad-raider-line"    { RET_TOKEN(UnitWoadRaiderLine) }
"cannon-galleon-line"    { RET_TOKEN(UnitCannonGalleonLine) }
"demolition-ship-line"    { RET_TOKEN(UnitDemolitionShipLine) }
"fire-ship-line"    { RET_TOKEN(UnitFireShipLine) }
"galley-line"    { RET_TOKEN(UnitGalleyLine) }
"longboat-line"    { RET_TOKEN(UnitLongboatLine) }
"turtle-ship-line"    { RET_TOKEN(UnitTurtleShipLine) }
"battering-ram-line"    { RET_TOKEN(UnitBatteringRamLine) }
"mangonel-line"    { RET_TOKEN(UnitMangonelLine) }
"scorpion-line"    { RET_TOKEN(UnitScorpionLine) }
"camel-line"    { RET_TOKEN(UnitCamelLine) }
"knight-line"    { RET_TOKEN(UnitKnightLine) }
"scout-cavalry-line"    { RET_TOKEN(UnitScoutCavalryLine) }
"my-elite-unique-unit"    { RET_TOKEN(UnitMyEliteUniqueUnit) }
"my-unique-unit"    { RET_TOKEN(UnitMyUniqueUnit) }
"my-unique-unit-line"    { RET_TOKEN(UnitMyUniqueUnitLine) }
"standard"    { RET_TOKEN(VictoryConditionNameStandard) }
"conquest"    { RET_TOKEN(VictoryConditionNameConquest) }
"time-limit"    { RET_TOKEN(VictoryConditionNameTimeLimit) }
"score"    { RET_TOKEN(VictoryConditionNameScore) }
"custom"    { RET_TOKEN(VictoryConditionNameCustom) }
"fortified-wall"    { RET_TOKEN(WallTypeFortifiedWall) }
"palisade-wall"    { RET_TOKEN(WallTypePalisadeWall) }
"stone-wall"    { RET_TOKEN(WallTypeStoneWall) }
"stone-wall-line"    { RET_TOKEN(WallTypeStoneWallLine) }
"acknowledge-event"    { RET_TOKEN_ENUM(AcknowledgeEvent, ActionType::AcknowledgeEvent) }
"acknowledge-taunt"    { RET_TOKEN_ENUM(AcknowledgeTaunt, ActionType::AcknowledgeTaunt) }
"attack-now"    { RET_TOKEN_ENUM(AttackNow, ActionType::AttackNow) }
"build"    { RET_TOKEN_ENUM(Build, ActionType::Build) }
"build-forward"    { RET_TOKEN_ENUM(BuildForward, ActionType::BuildForward) }
"build-gate"    { RET_TOKEN_ENUM(BuildGate, ActionType::BuildGate) }
"build-wall"    { RET_TOKEN_ENUM(BuildWall, ActionType::BuildWall) }
"buy-commodity"    { RET_TOKEN_ENUM(BuyCommodity, ActionType::BuyCommodity) }
"cc-add-resource"    { RET_TOKEN_ENUM(CcAddResource, ActionType::CcAddResource) }
"chat-local"    { RET_TOKEN_ENUM(ChatLocal, ActionType::ChatLocal) }
"chat-local-to-self"    { RET_TOKEN_ENUM(ChatLocalToSelf, ActionType::ChatLocalToSelf) }
"chat-local-using-id"    { RET_TOKEN_ENUM(ChatLocalUsingId, ActionType::ChatLocalUsingId) }
"chat-local-using-range"    { RET_TOKEN_ENUM(ChatLocalUsingRange, ActionType::ChatLocalUsingRange) }
"chat-to-all"    { RET_TOKEN_ENUM(ChatToAll, ActionType::ChatToAll) }
"chat-to-all-using-id"    { RET_TOKEN_ENUM(ChatToAllUsingId, ActionType::ChatToAllUsingId) }
"chat-to-all-using-range"    { RET_TOKEN_ENUM(ChatToAllUsingRange, ActionType::ChatToAllUsingRange) }
"chat-to-allies"    { RET_TOKEN_ENUM(ChatToAllies, ActionType::ChatToAllies) }
"chat-to-allies-using-id"    { RET_TOKEN_ENUM(ChatToAlliesUsingId, ActionType::ChatToAlliesUsingId) }
"chat-to-allies-using-range"    { RET_TOKEN_ENUM(ChatToAlliesUsingRange, ActionType::ChatToAlliesUsingRange) }
"chat-to-enemies"    { RET_TOKEN_ENUM(ChatToEnemies, ActionType::ChatToEnemies) }
"chat-to-enemies-using-id"    { RET_TOKEN_ENUM(ChatToEnemiesUsingId, ActionType::ChatToEnemiesUsingId) }
"chat-to-enemies-using-range"    { RET_TOKEN_ENUM(ChatToEnemiesUsingRange, ActionType::ChatToEnemiesUsingRange) }
"chat-to-player"    { RET_TOKEN_ENUM(ChatToPlayer, ActionType::ChatToPlayer) }
"chat-to-player-using-id"    { RET_TOKEN_ENUM(ChatToPlayerUsingId, ActionType::ChatToPlayerUsingId) }
"chat-to-player-using-range"    { RET_TOKEN_ENUM(ChatToPlayerUsingRange, ActionType::ChatToPlayerUsingRange) }
"chat-trace"    { RET_TOKEN_ENUM(ChatTrace, ActionType::ChatTrace) }
"clear-tribute-memory"    { RET_TOKEN_ENUM(ClearTributeMemory, ActionType::ClearTributeMemory) }
"delete-building"    { RET_TOKEN_ENUM(DeleteBuilding, ActionType::DeleteBuilding) }
"delete-unit"    { RET_TOKEN_ENUM(DeleteUnit, ActionType::DeleteUnit) }
"disable-self"    { RET_TOKEN_ENUM(DisableSelf, ActionType::DisableSelf) }
"disable-timer"    { RET_TOKEN_ENUM(DisableTimer, ActionType::DisableTimer) }
"do-nothing"    { RET_TOKEN_ENUM(DoNothing, ActionType::DoNothing) }
"enable-timer"    { RET_TOKEN_ENUM(EnableTimer, ActionType::EnableTimer) }
"enable-wall-placement"    { RET_TOKEN_ENUM(EnableWallPlacement, ActionType::EnableWallPlacement) }
"generate-random-number"    { RET_TOKEN_ENUM(GenerateRandomNumber, ActionType::GenerateRandomNumber) }
"log"    { RET_TOKEN_ENUM(Log, ActionType::Log) }
"log-trace"    { RET_TOKEN_ENUM(LogTrace, ActionType::LogTrace) }
"release-escrow"    { RET_TOKEN_ENUM(ReleaseEscrow, ActionType::ReleaseEscrow) }
"research"    { RET_TOKEN_ENUM(Research, ActionType::Research) }
"resign"    { RET_TOKEN_ENUM(Resign, ActionType::Resign) }
"sell-commodity"    { RET_TOKEN_ENUM(SellCommodity, ActionType::SellCommodity) }
"set-difficulty-parameter"    { RET_TOKEN_ENUM(SetDifficultyParameter, ActionType::SetDifficultyParameter) }
"set-doctrine"    { RET_TOKEN_ENUM(SetDoctrine, ActionType::SetDoctrine) }
"set-escrow-percentage"    { RET_TOKEN_ENUM(SetEscrowPercentage, ActionType::SetEscrowPercentage) }
"set-goal"    { RET_TOKEN_ENUM(SetGoal, ActionType::SetGoal) }
"set-shared-goal"    { RET_TOKEN_ENUM(SetSharedGoal, ActionType::SetSharedGoal) }
"set-signal"    { RET_TOKEN_ENUM(SetSignal, ActionType::SetSignal) }
"set-stance"    { RET_TOKEN_ENUM(SetStance, ActionType::SetStance) }
"set-strategic-number"    { RET_TOKEN_ENUM(SetStrategicNumber, ActionType::SetStrategicNumber) }
"spy"    { RET_TOKEN_ENUM(Spy, ActionType::Spy) }
"taunt"    { RET_TOKEN_ENUM(Taunt, ActionType::Taunt) }
"taunt-using-range"    { RET_TOKEN_ENUM(TauntUsingRange, ActionType::TauntUsingRange) }
"train"    { RET_TOKEN_ENUM(Train, ActionType::Train) }
"tribute-to-player"    { RET_TOKEN_ENUM(TributeToPlayer, ActionType::TributeToPlayer) }
"true"    { RET_TOKEN_ENUM(Trueval, Fact::Trueval) }
"false"    { RET_TOKEN_ENUM(Falseval, Fact::Falseval) }
"attack-soldier-count"    { RET_TOKEN_ENUM(AttackSoldierCount, Fact::AttackSoldierCount) }
"attack-warboat-count"    { RET_TOKEN_ENUM(AttackWarboatCount, Fact::AttackWarboatCount) }
"building-available"    { RET_TOKEN_ENUM(BuildingAvailable, Fact::BuildingAvailable) }
"building-count"    { RET_TOKEN_ENUM(BuildingCount, Fact::BuildingCount) }
"building-count-total"    { RET_TOKEN_ENUM(BuildingCountTotal, Fact::BuildingCountTotal) }
"building-type-count"    { RET_TOKEN_ENUM(BuildingTypeCount, Fact::BuildingTypeCount) }
"building-type-count-total"    { RET_TOKEN_ENUM(BuildingTypeCountTotal, Fact::BuildingTypeCountTotal) }
"can-afford-building"    { RET_TOKEN_ENUM(CanAffordBuilding, Fact::CanAffordBuilding) }
"can-afford-complete-wall"    { RET_TOKEN_ENUM(CanAffordCompleteWall, Fact::CanAffordCompleteWall) }
"can-afford-research"    { RET_TOKEN_ENUM(CanAffordResearch, Fact::CanAffordResearch) }
"can-afford-unit"    { RET_TOKEN_ENUM(CanAffordUnit, Fact::CanAffordUnit) }
"can-build"    { RET_TOKEN_ENUM(CanBuild, Fact::CanBuild) }
"can-build-gate"    { RET_TOKEN_ENUM(CanBuildGate, Fact::CanBuildGate) }
"can-build-gate-with-escrow"    { RET_TOKEN_ENUM(CanBuildGateWithEscrow, Fact::CanBuildGateWithEscrow) }
"can-build-wall"    { RET_TOKEN_ENUM(CanBuildWall, Fact::CanBuildWall) }
"can-build-wall-with-escrow"    { RET_TOKEN_ENUM(CanBuildWallWithEscrow, Fact::CanBuildWallWithEscrow) }
"can-build-with-escrow"    { RET_TOKEN_ENUM(CanBuildWithEscrow, Fact::CanBuildWithEscrow) }
"can-buy-commodity"    { RET_TOKEN_ENUM(CanBuyCommodity, Fact::CanBuyCommodity) }
"can-research"    { RET_TOKEN_ENUM(CanResearch, Fact::CanResearch) }
"can-research-with-escrow"    { RET_TOKEN_ENUM(CanResearchWithEscrow, Fact::CanResearchWithEscrow) }
"can-sell-commodity"    { RET_TOKEN_ENUM(CanSellCommodity, Fact::CanSellCommodity) }
"can-spy"    { RET_TOKEN_ENUM(CanSpy, Fact::CanSpy) }
"can-spy-with-escrow"    { RET_TOKEN_ENUM(CanSpyWithEscrow, Fact::CanSpyWithEscrow) }
"can-train"    { RET_TOKEN_ENUM(CanTrain, Fact::CanTrain) }
"can-train-with-escrow"    { RET_TOKEN_ENUM(CanTrainWithEscrow, Fact::CanTrainWithEscrow) }
"cc-players-building-count"    { RET_TOKEN_ENUM(CcPlayersBuildingCount, Fact::CcPlayersBuildingCount) }
"cc-players-building-type-count"    { RET_TOKEN_ENUM(CcPlayersBuildingTypeCount, Fact::CcPlayersBuildingTypeCount) }
"cc-players-unit-count"    { RET_TOKEN_ENUM(CcPlayersUnitCount, Fact::CcPlayersUnitCount) }
"cc-players-unit-type-count"    { RET_TOKEN_ENUM(CcPlayersUnitTypeCount, Fact::CcPlayersUnitTypeCount) }
"cheats-enabled"    { RET_TOKEN_ENUM(CheatsEnabled, Fact::CheatsEnabled) }
"civ-selected"    { RET_TOKEN_ENUM(CivSelected, Fact::CivSelected) }
"civilian-population"    { RET_TOKEN_ENUM(CivilianPopulation, Fact::CivilianPopulation) }
"commodity-buying-price"    { RET_TOKEN_ENUM(CommodityBuyingPrice, Fact::CommodityBuyingPrice) }
"commodity-selling-price"    { RET_TOKEN_ENUM(CommoditySellingPrice, Fact::CommoditySellingPrice) }
"current-age"    { RET_TOKEN_ENUM(CurrentAge, Fact::CurrentAge) }
"current-age-time"    { RET_TOKEN_ENUM(CurrentAgeTime, Fact::CurrentAgeTime) }
"current-score"    { RET_TOKEN_ENUM(CurrentScore, Fact::CurrentScore) }
"death-match-game"    { RET_TOKEN_ENUM(DeathMatchGame, Fact::DeathMatchGame) }
"defend-soldier-count"    { RET_TOKEN_ENUM(DefendSoldierCount, Fact::DefendSoldierCount) }
"defend-warboat-count"    { RET_TOKEN_ENUM(DefendWarboatCount, Fact::DefendWarboatCount) }
"difficulty"    { RET_TOKEN_ENUM(Difficulty, Fact::Difficulty) }
"doctrine"    { RET_TOKEN_ENUM(Doctrine, Fact::Doctrine) }
"dropsite-min-distance"    { RET_TOKEN_ENUM(DropsiteMinDistance, Fact::DropsiteMinDistance) }
"enemy-buildings-in-town"    { RET_TOKEN_ENUM(EnemyBuildingsInTown, Fact::EnemyBuildingsInTown) }
"enemy-captured-relics"    { RET_TOKEN_ENUM(EnemyCapturedRelics, Fact::EnemyCapturedRelics) }
"escrow-amount"    { RET_TOKEN_ENUM(EscrowAmount, Fact::EscrowAmount) }
"event-detected"    { RET_TOKEN_ENUM(EventDetected, Fact::EventDetected) }
"food-amount"    { RET_TOKEN_ENUM(FoodAmount, Fact::FoodAmount) }
"game-time"    { RET_TOKEN_ENUM(GameTime, Fact::GameTime) }
"goal"    { RET_TOKEN_ENUM(Goal, Fact::Goal) }
"gold-amount"    { RET_TOKEN_ENUM(GoldAmount, Fact::GoldAmount) }
"housing-headroom"    { RET_TOKEN_ENUM(HousingHeadroom, Fact::HousingHeadroom) }
"idle-farm-count"    { RET_TOKEN_ENUM(IdleFarmCount, Fact::IdleFarmCount) }
"map-size"    { RET_TOKEN_ENUM(MapSize, Fact::MapSize) }
"map-type"    { RET_TOKEN_ENUM(MapType, Fact::MapType) }
"military-population"    { RET_TOKEN_ENUM(MilitaryPopulation, Fact::MilitaryPopulation) }
"player-computer"    { RET_TOKEN_ENUM(PlayerComputer, Fact::PlayerComputer) }
"player-human"    { RET_TOKEN_ENUM(PlayerHuman, Fact::PlayerHuman) }
"player-in-game"    { RET_TOKEN_ENUM(PlayerInGame, Fact::PlayerInGame) }
"player-number"    { RET_TOKEN_ENUM(PlayerNumber, Fact::PlayerNumber) }
"player-resigned"    { RET_TOKEN_ENUM(PlayerResigned, Fact::PlayerResigned) }
"player-valid"    { RET_TOKEN_ENUM(PlayerValid, Fact::PlayerValid) }
"players-building-count"    { RET_TOKEN_ENUM(PlayersBuildingCount, Fact::PlayersBuildingCount) }
"players-building-type-count"    { RET_TOKEN_ENUM(PlayersBuildingTypeCount, Fact::PlayersBuildingTypeCount) }
"players-civ"    { RET_TOKEN_ENUM(PlayersCiv, Fact::PlayersCiv) }
"players-civilian-population"    { RET_TOKEN_ENUM(PlayersCivilianPopulation, Fact::PlayersCivilianPopulation) }
"players-current-age"    { RET_TOKEN_ENUM(PlayersCurrentAge, Fact::PlayersCurrentAge) }
"players-current-age-time"    { RET_TOKEN_ENUM(PlayersCurrentAgeTime, Fact::PlayersCurrentAgeTime) }
"players-military-population"    { RET_TOKEN_ENUM(PlayersMilitaryPopulation, Fact::PlayersMilitaryPopulation) }
"players-population"    { RET_TOKEN_ENUM(PlayersPopulation, Fact::PlayersPopulation) }
"players-score"    { RET_TOKEN_ENUM(PlayersScore, Fact::PlayersScore) }
"players-stance"    { RET_TOKEN_ENUM(PlayersStance, Fact::PlayersStance) }
"players-tribute"    { RET_TOKEN_ENUM(PlayersTribute, Fact::PlayersTribute) }
"players-tribute-memory"    { RET_TOKEN_ENUM(PlayersTributeMemory, Fact::PlayersTributeMemory) }
"players-unit-count"    { RET_TOKEN_ENUM(PlayersUnitCount, Fact::PlayersUnitCount) }
"players-unit-type-count"    { RET_TOKEN_ENUM(PlayersUnitTypeCount, Fact::PlayersUnitTypeCount) }
"population"    { RET_TOKEN_ENUM(Population, Fact::Population) }
"population-cap"    { RET_TOKEN_ENUM(PopulationCap, Fact::PopulationCap) }
"population-headroom"    { RET_TOKEN_ENUM(PopulationHeadroom, Fact::PopulationHeadroom) }
"random-number"    { RET_TOKEN_ENUM(RandomNumber, Fact::RandomNumber) }
"regicide-game"    { RET_TOKEN_ENUM(RegicideGame, Fact::RegicideGame) }
"research-available"    { RET_TOKEN_ENUM(ResearchAvailable, Fact::ResearchAvailable) }
"research-completed"    { RET_TOKEN_ENUM(ResearchCompleted, Fact::ResearchCompleted) }
"resource-found"    { RET_TOKEN_ENUM(ResourceFound, Fact::ResourceFound) }
"shared-goal"    { RET_TOKEN_ENUM(SharedGoal, Fact::SharedGoal) }
"sheep-and-forage-too-far"    { RET_TOKEN_ENUM(SheepAndForageTooFar, Fact::SheepAndForageTooFar) }
"soldier-count"    { RET_TOKEN_ENUM(SoldierCount, Fact::SoldierCount) }
"stance-toward"    { RET_TOKEN_ENUM(StanceToward, Fact::StanceToward) }
"starting-age"    { RET_TOKEN_ENUM(StartingAge, Fact::StartingAge) }
"starting-resources"    { RET_TOKEN_ENUM(StartingResources, Fact::StartingResources) }
"stone-amount"    { RET_TOKEN_ENUM(StoneAmount, Fact::StoneAmount) }
"strategic-number"    { RET_TOKEN_ENUM(StrategicNumber, Fact::StrategicNumber) }
"taunt-detected"    { RET_TOKEN_ENUM(TauntDetected, Fact::TauntDetected) }
"timer-triggered"    { RET_TOKEN_ENUM(TimerTriggered, Fact::TimerTriggered) }
"town-under-attack"    { RET_TOKEN_ENUM(TownUnderAttack, Fact::TownUnderAttack) }
"unit-available"    { RET_TOKEN_ENUM(UnitAvailable, Fact::UnitAvailable) }
"unit-count"    { RET_TOKEN_ENUM(UnitCount, Fact::UnitCount) }
"unit-count-total"    { RET_TOKEN_ENUM(UnitCountTotal, Fact::UnitCountTotal) }
"unit-type-count"    { RET_TOKEN_ENUM(UnitTypeCount, Fact::UnitTypeCount) }
"unit-type-count-total"    { RET_TOKEN_ENUM(UnitTypeCountTotal, Fact::UnitTypeCountTotal) }
"victory-condition"    { RET_TOKEN_ENUM(VictoryCondition, Fact::VictoryCondition) }
"wall-completed-percentage"    { RET_TOKEN_ENUM(WallCompletedPercentage, Fact::WallCompletedPercentage) }
"wall-invisible-percentage"    { RET_TOKEN_ENUM(WallInvisiblePercentage, Fact::WallInvisiblePercentage) }
"warboat-count"    { RET_TOKEN_ENUM(WarboatCount, Fact::WarboatCount) }
"wood-amount"    { RET_TOKEN_ENUM(WoodAmount, Fact::WoodAmount) }

"("                 RET_TOKEN(OpenParen)
")"                 RET_TOKEN(CloseParen)
"defrule"           RET_TOKEN(RuleStart)
"=>"                RET_TOKEN(ConditionActionSeparator)

"not"               RET_TOKEN(Not)
"or"                RET_TOKEN(Or)

"<"                 RET_TOKEN(RelOpLessThan)
"<="                RET_TOKEN(RelOpLessOrEqual)
">"                 RET_TOKEN(RelOpGreaterThan)
">="                RET_TOKEN(RelOpGreaterOrEqual)
"=="                RET_TOKEN(RelOpEqual)

"#load-if-defined"  RET_TOKEN(LoadIfDefined)
"#else"             RET_TOKEN(Else)
"#end-if"           RET_TOKEN(EndIf)

[\r\n]+

{symbolname}        RET_STRING(SymbolName)
{string}            RET_STRING(String)
{number}            RET_INT(Number)

%%
