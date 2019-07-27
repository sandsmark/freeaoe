%option case-insensitive
%option noyywrap
%option yylineno

%{
    #include "ScriptLoader.h"
    #include "ScriptTokenizer.h"
    #include "grammar.gen.tab.hh"
    #include "location.hh"

    //static ai::location loc;

    //#define YY_USER_ACTION loc.step(); loc.columns(yyleng);

    //#undef  YY_DECL
    //#define YY_DECL ai::ScriptParser::symbol_type ai::ScriptTokenizer::yylex(ai::ScriptLoader &driver)

    //#define yyterminate() return ai::ScriptParser::make_ScriptEnd(loc);

    //#define RET_TOKEN(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, loc);
    //#define RET_STRING(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, yytext, loc);
    //#define RET_INT(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, atoi(yytext), loc); 

    #define RET_TOKEN(token_name) return token_name;
    #define RET_STRING(token_name) yylval.string = yytext; return String
    #define RET_INT(token_name) yylval.number = atoi(yytext); return Number; 
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
"food"    { RET_TOKEN(CommodityFood) }
"stone"    { RET_TOKEN(CommodityStone) }
"wood"    { RET_TOKEN(CommodityWood) }
"gold"    { RET_TOKEN(CommodityGold) }
"easiest"    { RET_TOKEN(DifficultyEasiest) }
"easy"    { RET_TOKEN(DifficultyEasy) }
"moderate"    { RET_TOKEN(DifficultyModerate) }
"hard"    { RET_TOKEN(DifficultyHard) }
"hardest"    { RET_TOKEN(DifficultyHardest) }
"ability-to-dodge-missiles"    { RET_TOKEN(DifficultyParameterAbilityToDodgeMissiles) }
"ability-to-maintain-distance"    { RET_TOKEN(DifficultyParameterAbilityToMaintainDistance) }
"ally"    { RET_TOKEN(DiplomaticStanceAlly) }
"neutral"    { RET_TOKEN(DiplomaticStanceNeutral) }
"enemy"    { RET_TOKEN(DiplomaticStanceEnemy) }
"trigger"    { RET_TOKEN(EventTypeTrigger) }
"tiny"    { RET_TOKEN(MapSizeTiny) }
"small"    { RET_TOKEN(MapSizeSmall) }
"medium"    { RET_TOKEN(MapSizeMedium) }
"normal"    { RET_TOKEN(MapSizeNormal) }
"large"    { RET_TOKEN(MapSizeLarge) }
"giant"    { RET_TOKEN(MapSizeGiant) }
"arabia"    { RET_TOKEN(MapTypeArabia) }
"archipelago"    { RET_TOKEN(MapTypeArchipelago) }
"baltic"    { RET_TOKEN(MapTypeBaltic) }
"black-forest"    { RET_TOKEN(MapTypeBlackForest) }
"coastal"    { RET_TOKEN(MapTypeCoastal) }
"continental"    { RET_TOKEN(MapTypeContinental) }
"crater-lake"    { RET_TOKEN(MapTypeCraterLake) }
"fortress"    { RET_TOKEN(MapTypeFortress) }
"gold-rush"    { RET_TOKEN(MapTypeGoldRush) }
"highland"    { RET_TOKEN(MapTypeHighland) }
"islands"    { RET_TOKEN(MapTypeIslands) }
"mediterranean"    { RET_TOKEN(MapTypeMediterranean) }
"migration"    { RET_TOKEN(MapTypeMigration) }
"rivers"    { RET_TOKEN(MapTypeRivers) }
"team-islands"    { RET_TOKEN(MapTypeTeamIslands) }
"scenario-map"    { RET_TOKEN(MapTypeScenarioMap) }
"any-ally"    { RET_TOKEN(PlayerNumberAnyAlly) }
"any-computer"    { RET_TOKEN(PlayerNumberAnyComputer) }
"any-computer-ally"    { RET_TOKEN(PlayerNumberAnyComputerAlly) }
"any-computer-enemy"    { RET_TOKEN(PlayerNumberAnyComputerEnemy) }
"any-computer-neutral"    { RET_TOKEN(PlayerNumberAnyComputerNeutral) }
"any-enemy"    { RET_TOKEN(PlayerNumberAnyEnemy) }
"any-human"    { RET_TOKEN(PlayerNumberAnyHuman) }
"any-human-ally"    { RET_TOKEN(PlayerNumberAnyHumanAlly) }
"any-human-enemy"    { RET_TOKEN(PlayerNumberAnyHumanEnemy) }
"any-human-neutral"    { RET_TOKEN(PlayerNumberAnyHumanNeutral) }
"any-neutral"    { RET_TOKEN(PlayerNumberAnyNeutral) }
"every-ally"    { RET_TOKEN(PlayerNumberEveryAlly) }
"every-computer"    { RET_TOKEN(PlayerNumberEveryComputer) }
"every-enemy"    { RET_TOKEN(PlayerNumberEveryEnemy) }
"every-human"    { RET_TOKEN(PlayerNumberEveryHuman) }
"every-neutral"    { RET_TOKEN(PlayerNumberEveryNeutral) }
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
"low-resources"    { RET_TOKEN(StartingResourcesLowResources) }
"medium-resources"    { RET_TOKEN(StartingResourcesMediumResources) }
"high-resources"    { RET_TOKEN(StartingResourcesHighResources) }
"sn-percent-civilian-explorers"    { RET_TOKEN(StrategicNumberSnPercentCivilianExplorers) }
"sn-percent-civilian-builders"    { RET_TOKEN(StrategicNumberSnPercentCivilianBuilders) }
"sn-percent-civilian-gatherers"    { RET_TOKEN(StrategicNumberSnPercentCivilianGatherers) }
"sn-cap-civilian-explorers"    { RET_TOKEN(StrategicNumberSnCapCivilianExplorers) }
"sn-cap-civilian-builders"    { RET_TOKEN(StrategicNumberSnCapCivilianBuilders) }
"sn-cap-civilian-gatherers"    { RET_TOKEN(StrategicNumberSnCapCivilianGatherers) }
"sn-minimum-attack-group-size"    { RET_TOKEN(StrategicNumberSnMinimumAttackGroupSize) }
"sn-total-number-explorers"    { RET_TOKEN(StrategicNumberSnTotalNumberExplorers) }
"sn-percent-enemy-sighted-response"    { RET_TOKEN(StrategicNumberSnPercentEnemySightedResponse) }
"sn-enemy-sighted-response-distance"    { RET_TOKEN(StrategicNumberSnEnemySightedResponseDistance) }
"sn-sentry-distance"    { RET_TOKEN(StrategicNumberSnSentryDistance) }
"sn-relic-return-distance"    { RET_TOKEN(StrategicNumberSnRelicReturnDistance) }
"sn-minimum-defend-group-size"    { RET_TOKEN(StrategicNumberSnMinimumDefendGroupSize) }
"sn-maximum-attack-group-size"    { RET_TOKEN(StrategicNumberSnMaximumAttackGroupSize) }
"sn-maximum-defend-group-size"    { RET_TOKEN(StrategicNumberSnMaximumDefendGroupSize) }
"sn-minimum-peace-like-level"    { RET_TOKEN(StrategicNumberSnMinimumPeaceLikeLevel) }
"sn-percent-exploration-required"    { RET_TOKEN(StrategicNumberSnPercentExplorationRequired) }
"sn-zero-priority-distance"    { RET_TOKEN(StrategicNumberSnZeroPriorityDistance) }
"sn-minimum-civilian-explorers"    { RET_TOKEN(StrategicNumberSnMinimumCivilianExplorers) }
"sn-number-attack-groups"    { RET_TOKEN(StrategicNumberSnNumberAttackGroups) }
"sn-number-defend-groups"    { RET_TOKEN(StrategicNumberSnNumberDefendGroups) }
"sn-attack-group-gather-spacing"    { RET_TOKEN(StrategicNumberSnAttackGroupGatherSpacing) }
"sn-number-explore-groups"    { RET_TOKEN(StrategicNumberSnNumberExploreGroups) }
"sn-minimum-explore-group-size"    { RET_TOKEN(StrategicNumberSnMinimumExploreGroupSize) }
"sn-maximum-explore-group-size"    { RET_TOKEN(StrategicNumberSnMaximumExploreGroupSize) }
"sn-gold-defend-priority"    { RET_TOKEN(StrategicNumberSnGoldDefendPriority) }
"sn-stone-defend-priority"    { RET_TOKEN(StrategicNumberSnStoneDefendPriority) }
"sn-forage-defend-priority"    { RET_TOKEN(StrategicNumberSnForageDefendPriority) }
"sn-relic-defend-priority"    { RET_TOKEN(StrategicNumberSnRelicDefendPriority) }
"sn-town-defend-priority"    { RET_TOKEN(StrategicNumberSnTownDefendPriority) }
"sn-defense-distance"    { RET_TOKEN(StrategicNumberSnDefenseDistance) }
"sn-number-boat-attack-groups"    { RET_TOKEN(StrategicNumberSnNumberBoatAttackGroups) }
"sn-minimum-boat-attack-group-size"    { RET_TOKEN(StrategicNumberSnMinimumBoatAttackGroupSize) }
"sn-maximum-boat-attack-group-size"    { RET_TOKEN(StrategicNumberSnMaximumBoatAttackGroupSize) }
"sn-number-boat-explore-groups"    { RET_TOKEN(StrategicNumberSnNumberBoatExploreGroups) }
"sn-minimum-boat-explore-group-size"    { RET_TOKEN(StrategicNumberSnMinimumBoatExploreGroupSize) }
"sn-maximum-boat-explore-group-size"    { RET_TOKEN(StrategicNumberSnMaximumBoatExploreGroupSize) }
"sn-number-boat-defend-groups"    { RET_TOKEN(StrategicNumberSnNumberBoatDefendGroups) }
"sn-minimum-boat-defend-group-size"    { RET_TOKEN(StrategicNumberSnMinimumBoatDefendGroupSize) }
"sn-maximum-boat-defend-group-size"    { RET_TOKEN(StrategicNumberSnMaximumBoatDefendGroupSize) }
"sn-dock-defend-priority"    { RET_TOKEN(StrategicNumberSnDockDefendPriority) }
"sn-sentry-distance-variation"    { RET_TOKEN(StrategicNumberSnSentryDistanceVariation) }
"sn-minimum-town-size"    { RET_TOKEN(StrategicNumberSnMinimumTownSize) }
"sn-maximum-town-size"    { RET_TOKEN(StrategicNumberSnMaximumTownSize) }
"sn-group-commander-selection-method"    { RET_TOKEN(StrategicNumberSnGroupCommanderSelectionMethod) }
"sn-consecutive-idle-unit-limit"    { RET_TOKEN(StrategicNumberSnConsecutiveIdleUnitLimit) }
"sn-target-evaluation-distance"    { RET_TOKEN(StrategicNumberSnTargetEvaluationDistance) }
"sn-target-evaluation-hitpoints"    { RET_TOKEN(StrategicNumberSnTargetEvaluationHitpoints) }
"sn-target-evaluation-damage-capability"    { RET_TOKEN(StrategicNumberSnTargetEvaluationDamageCapability) }
"sn-target-evaluation-kills"    { RET_TOKEN(StrategicNumberSnTargetEvaluationKills) }
"sn-target-evaluation-ally-proximity"    { RET_TOKEN(StrategicNumberSnTargetEvaluationAllyProximity) }
"sn-target-evaluation-rof"    { RET_TOKEN(StrategicNumberSnTargetEvaluationRof) }
"sn-target-evaluation-randomness"    { RET_TOKEN(StrategicNumberSnTargetEvaluationRandomness) }
"sn-camp-max-distance"    { RET_TOKEN(StrategicNumberSnCampMaxDistance) }
"sn-mill-max-distance"    { RET_TOKEN(StrategicNumberSnMillMaxDistance) }
"sn-target-evaluation-attack-attempts"    { RET_TOKEN(StrategicNumberSnTargetEvaluationAttackAttempts) }
"sn-target-evaluation-range"    { RET_TOKEN(StrategicNumberSnTargetEvaluationRange) }
"sn-defend-overlap-distance"    { RET_TOKEN(StrategicNumberSnDefendOverlapDistance) }
"sn-scale-minimum-attack-group-size"    { RET_TOKEN(StrategicNumberSnScaleMinimumAttackGroupSize) }
"sn-scale-maximum-attack-group-size"    { RET_TOKEN(StrategicNumberSnScaleMaximumAttackGroupSize) }
"sn-attack-group-size-randomness"    { RET_TOKEN(StrategicNumberSnAttackGroupSizeRandomness) }
"sn-scaling-frequency"    { RET_TOKEN(StrategicNumberSnScalingFrequency) }
"sn-maximum-gaia-attack-response"    { RET_TOKEN(StrategicNumberSnMaximumGaiaAttackResponse) }
"sn-build-frequency"    { RET_TOKEN(StrategicNumberSnBuildFrequency) }
"sn-attack-separation-time-randomness"    { RET_TOKEN(StrategicNumberSnAttackSeparationTimeRandomness) }
"sn-attack-intelligence"    { RET_TOKEN(StrategicNumberSnAttackIntelligence) }
"sn-initial-attack-delay"    { RET_TOKEN(StrategicNumberSnInitialAttackDelay) }
"sn-save-scenario-information"    { RET_TOKEN(StrategicNumberSnSaveScenarioInformation) }
"sn-special-attack-type1"    { RET_TOKEN(StrategicNumberSnSpecialAttackType1) }
"sn-special-attack-influence1"    { RET_TOKEN(StrategicNumberSnSpecialAttackInfluence1) }
"sn-minimum-water-body-size-for-dock"    { RET_TOKEN(StrategicNumberSnMinimumWaterBodySizeForDock) }
"sn-number-build-attempts-before-skip"    { RET_TOKEN(StrategicNumberSnNumberBuildAttemptsBeforeSkip) }
"sn-max-skips-per-attempt"    { RET_TOKEN(StrategicNumberSnMaxSkipsPerAttempt) }
"sn-food-gatherer-percentage"    { RET_TOKEN(StrategicNumberSnFoodGathererPercentage) }
"sn-gold-gatherer-percentage"    { RET_TOKEN(StrategicNumberSnGoldGathererPercentage) }
"sn-stone-gatherer-percentage"    { RET_TOKEN(StrategicNumberSnStoneGathererPercentage) }
"sn-wood-gatherer-percentage"    { RET_TOKEN(StrategicNumberSnWoodGathererPercentage) }
"sn-target-evaluation-continent"    { RET_TOKEN(StrategicNumberSnTargetEvaluationContinent) }
"sn-target-evaluation-siege-weapon"    { RET_TOKEN(StrategicNumberSnTargetEvaluationSiegeWeapon) }
"sn-group-leader-defense-distance"    { RET_TOKEN(StrategicNumberSnGroupLeaderDefenseDistance) }
"sn-initial-attack-delay-type"    { RET_TOKEN(StrategicNumberSnInitialAttackDelayType) }
"sn-blot-exploration-map"    { RET_TOKEN(StrategicNumberSnBlotExplorationMap) }
"sn-blot-size"    { RET_TOKEN(StrategicNumberSnBlotSize) }
"sn-intelligent-gathering"    { RET_TOKEN(StrategicNumberSnIntelligentGathering) }
"sn-task-ungrouped-soldiers"    { RET_TOKEN(StrategicNumberSnTaskUngroupedSoldiers) }
"sn-target-evaluation-boat"    { RET_TOKEN(StrategicNumberSnTargetEvaluationBoat) }
"sn-number-enemy-objects-required"    { RET_TOKEN(StrategicNumberSnNumberEnemyObjectsRequired) }
"sn-number-max-skip-cycles"    { RET_TOKEN(StrategicNumberSnNumberMaxSkipCycles) }
"sn-retask-gather-amount"    { RET_TOKEN(StrategicNumberSnRetaskGatherAmount) }
"sn-max-retask-gather-amount"    { RET_TOKEN(StrategicNumberSnMaxRetaskGatherAmount) }
"sn-max-build-plan-gatherer-percentage"    { RET_TOKEN(StrategicNumberSnMaxBuildPlanGathererPercentage) }
"sn-food-dropsite-distance"    { RET_TOKEN(StrategicNumberSnFoodDropsiteDistance) }
"sn-wood-dropsite-distance"    { RET_TOKEN(StrategicNumberSnWoodDropsiteDistance) }
"sn-stone-dropsite-distance"    { RET_TOKEN(StrategicNumberSnStoneDropsiteDistance) }
"sn-gold-dropsite-distance"    { RET_TOKEN(StrategicNumberSnGoldDropsiteDistance) }
"sn-initial-exploration-required"    { RET_TOKEN(StrategicNumberSnInitialExplorationRequired) }
"sn-random-placement-factor"    { RET_TOKEN(StrategicNumberSnRandomPlacementFactor) }
"sn-required-forest-tiles"    { RET_TOKEN(StrategicNumberSnRequiredForestTiles) }
"sn-attack-diplomacy-impact"    { RET_TOKEN(StrategicNumberSnAttackDiplomacyImpact) }
"sn-percent-half-exploration"    { RET_TOKEN(StrategicNumberSnPercentHalfExploration) }
"sn-target-evaluation-time-kill-ratio"    { RET_TOKEN(StrategicNumberSnTargetEvaluationTimeKillRatio) }
"sn-target-evaluation-in-progress"    { RET_TOKEN(StrategicNumberSnTargetEvaluationInProgress) }
"sn-attack-winning-player"    { RET_TOKEN(StrategicNumberSnAttackWinningPlayer) }
"sn-coop-share-information"    { RET_TOKEN(StrategicNumberSnCoopShareInformation) }
"sn-attack-winning-player-factor"    { RET_TOKEN(StrategicNumberSnAttackWinningPlayerFactor) }
"sn-coop-share-attacking"    { RET_TOKEN(StrategicNumberSnCoopShareAttacking) }
"sn-coop-share-attacking-interval"    { RET_TOKEN(StrategicNumberSnCoopShareAttackingInterval) }
"sn-percentage-explore-exterminators"    { RET_TOKEN(StrategicNumberSnPercentageExploreExterminators) }
"sn-track-player-history"    { RET_TOKEN(StrategicNumberSnTrackPlayerHistory) }
"sn-minimum-dropsite-buffer"    { RET_TOKEN(StrategicNumberSnMinimumDropsiteBuffer) }
"sn-use-by-type-max-gathering"    { RET_TOKEN(StrategicNumberSnUseByTypeMaxGathering) }
"sn-minimum-boar-hunt-group-size"    { RET_TOKEN(StrategicNumberSnMinimumBoarHuntGroupSize) }
"sn-minimum-amount-for-trading"    { RET_TOKEN(StrategicNumberSnMinimumAmountForTrading) }
"sn-easiest-reaction-percentage"    { RET_TOKEN(StrategicNumberSnEasiestReactionPercentage) }
"sn-easier-reaction-percentage"    { RET_TOKEN(StrategicNumberSnEasierReactionPercentage) }
"sn-hits-before-alliance-change"    { RET_TOKEN(StrategicNumberSnHitsBeforeAllianceChange) }
"sn-allow-civilian-defense"    { RET_TOKEN(StrategicNumberSnAllowCivilianDefense) }
"sn-number-forward-builders"    { RET_TOKEN(StrategicNumberSnNumberForwardBuilders) }
"sn-percent-attack-soldiers"    { RET_TOKEN(StrategicNumberSnPercentAttackSoldiers) }
"sn-percent-attack-boats"    { RET_TOKEN(StrategicNumberSnPercentAttackBoats) }
"sn-do-not-scale-for-difficulty-level"    { RET_TOKEN(StrategicNumberSnDoNotScaleForDifficultyLevel) }
"sn-group-form-distance"    { RET_TOKEN(StrategicNumberSnGroupFormDistance) }
"sn-ignore-attack-group-under-attack"    { RET_TOKEN(StrategicNumberSnIgnoreAttackGroupUnderAttack) }
"sn-gather-defense-units"    { RET_TOKEN(StrategicNumberSnGatherDefenseUnits) }
"sn-maximum-wood-drop-distance"    { RET_TOKEN(StrategicNumberSnMaximumWoodDropDistance) }
"sn-maximum-food-drop-distance"    { RET_TOKEN(StrategicNumberSnMaximumFoodDropDistance) }
"sn-maximum-hunt-drop-distance"    { RET_TOKEN(StrategicNumberSnMaximumHuntDropDistance) }
"sn-maximum-fish-boat-drop-distance"    { RET_TOKEN(StrategicNumberSnMaximumFishBoatDropDistance) }
"sn-maximum-gold-drop-distance"    { RET_TOKEN(StrategicNumberSnMaximumGoldDropDistance) }
"sn-maximum-stone-drop-distance"    { RET_TOKEN(StrategicNumberSnMaximumStoneDropDistance) }
"sn-gather-idle-soldiers-at-center"    { RET_TOKEN(StrategicNumberSnGatherIdleSoldiersAtCenter) }
"sn-garrison-rams"    { RET_TOKEN(StrategicNumberSnGarrisonRams) }
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
"standard"    { RET_TOKEN(VictoryConditionStandard) }
"conquest"    { RET_TOKEN(VictoryConditionConquest) }
"time-limit"    { RET_TOKEN(VictoryConditionTimeLimit) }
"score"    { RET_TOKEN(VictoryConditionScore) }
"custom"    { RET_TOKEN(VictoryConditionCustom) }
"fortified-wall"    { RET_TOKEN(WallTypeFortifiedWall) }
"palisade-wall"    { RET_TOKEN(WallTypePalisadeWall) }
"stone-wall"    { RET_TOKEN(WallTypeStoneWall) }
"stone-wall-line"    { RET_TOKEN(WallTypeStoneWallLine) }

"("                 RET_TOKEN(OpenParen)
")"                 RET_TOKEN(CloseParen)
"defrule"           RET_TOKEN(RuleStart)
"=>"                RET_TOKEN(ConditionActionSeparator)

"not"               RET_TOKEN(Not)
"or"                RET_TOKEN(Or)

"<"                 RET_TOKEN(LessThan)
"<="                RET_TOKEN(LessOrEqual)
">"                 RET_TOKEN(GreaterThan)
">="                RET_TOKEN(GreaterOrEqual)
"=="                RET_TOKEN(Equal)

"#load-if-defined"  RET_TOKEN(LoadIfDefined)
"#else"             RET_TOKEN(Else)
"#end-if"           RET_TOKEN(EndIf)

[\r\n]+

{symbolname}        RET_STRING(SymbolName)
{string}            RET_STRING(String)
{number}            RET_INT(Number)

%%
