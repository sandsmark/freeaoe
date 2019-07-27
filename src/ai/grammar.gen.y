%{

#include <string.h>
#include <stdio.h>

extern int yylex(void);
extern int yyparse(void);
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
	int number;
	const char *string;
}

%destructor { free($$); $$ = NULL; } String SymbolName;


%token<number> Number
%token<string> String
%token<string> SymbolName

%token OpenParen CloseParen
%token RuleStart ConditionActionSeparator

%token LessThan LessOrEqual GreaterThan GreaterOrEqual Equal Not Or

%token LoadIfDefined Else EndIf

%token Space NewLine

%start aiscript
%token AgeDarkAge AgeFeudalAge AgeCastleAge AgeImperialAge AgePostImperialAge
%token BuildingArcheryRange BuildingBarracks BuildingBlacksmith BuildingBombardTower BuildingCastle BuildingDock BuildingFarm BuildingFishTrap BuildingGuardTower BuildingHouse BuildingKeep BuildingLumberCamp BuildingMarket BuildingMill BuildingMiningCamp BuildingMonastery BuildingOutpost BuildingSiegeWorkshop BuildingStable BuildingTownCenter BuildingUniversity BuildingWatchTower BuildingWonder BuildingWatchTowerLine
%token CivBriton CivByzantine CivCeltic CivChinese CivFrankish CivGothic CivJapanese CivMongol CivPersian CivSaracen CivTeutonic CivTurkish CivViking
%token CommodityFood CommodityStone CommodityWood CommodityGold
%token DifficultyEasiest DifficultyEasy DifficultyModerate DifficultyHard DifficultyHardest
%token DifficultyParameterAbilityToDodgeMissiles DifficultyParameterAbilityToMaintainDistance
%token DiplomaticStanceAlly DiplomaticStanceNeutral DiplomaticStanceEnemy
%token EventTypeTrigger
%token MapSizeTiny MapSizeSmall MapSizeMedium MapSizeNormal MapSizeLarge MapSizeGiant
%token MapTypeArabia MapTypeArchipelago MapTypeBaltic MapTypeBlackForest MapTypeCoastal MapTypeContinental MapTypeCraterLake MapTypeFortress MapTypeGoldRush MapTypeHighland MapTypeIslands MapTypeMediterranean MapTypeMigration MapTypeRivers MapTypeTeamIslands MapTypeScenarioMap
%token PlayerNumberAnyAlly PlayerNumberAnyComputer PlayerNumberAnyComputerAlly PlayerNumberAnyComputerEnemy PlayerNumberAnyComputerNeutral PlayerNumberAnyEnemy PlayerNumberAnyHuman PlayerNumberAnyHumanAlly PlayerNumberAnyHumanEnemy PlayerNumberAnyHumanNeutral PlayerNumberAnyNeutral PlayerNumberEveryAlly PlayerNumberEveryComputer PlayerNumberEveryEnemy PlayerNumberEveryHuman PlayerNumberEveryNeutral
%token RelOpLessThan RelOpLessOrEqual RelOpGreaterThan RelOpGreaterOrEqual RelOpEqual RelOpNotEqual
%token ResearchItemRiArbalest ResearchItemRiCrossbow ResearchItemRiEliteSkirmisher ResearchItemRiHandCannon ResearchItemRiHeavyCavalryArcher ResearchItemRiChampion ResearchItemRiEliteEagleWarrior ResearchItemRiHalberdier ResearchItemRiLongSwordsman ResearchItemRiManAtArms ResearchItemRiParthianTactics ResearchItemRiPikeman ResearchItemRiSquires ResearchItemRiThumbRing ResearchItemRiTracking ResearchItemRiTwoHandedSwordsman ResearchItemRiBlastFurnace ResearchItemRiBodkinArrow ResearchItemRiBracer ResearchItemRiChainBarding ResearchItemRiChainMail ResearchItemRiFletching ResearchItemRiForging ResearchItemRiIronCasting ResearchItemRiLeatherArcherArmor ResearchItemRiPaddedArcherArmor ResearchItemRiPlateBarding ResearchItemRiPlateMail ResearchItemRiRingArcherArmor ResearchItemRiScaleBarding ResearchItemRiScaleMail ResearchItemRiConscription ResearchItemRiHoardings ResearchItemRiSappers ResearchItemRiEliteBerserk ResearchItemRiEliteCataphract ResearchItemRiEliteChuKoNu ResearchItemRiEliteHuskarl ResearchItemRiEliteJanissary ResearchItemRiEliteLongbowman ResearchItemRiEliteMameluke ResearchItemRiEliteMangudai ResearchItemRiEliteSamurai ResearchItemRiEliteTeutonicKnight ResearchItemRiEliteThrowingAxeman ResearchItemRiEliteWarElephant ResearchItemRiEliteWoadRaider ResearchItemRiMyUniqueEliteUnit ResearchItemRiMyUniqueResearch ResearchItemRiCannonGalleon ResearchItemRiCareening ResearchItemRiDeckGuns ResearchItemRiDryDock ResearchItemRiEliteLongboat ResearchItemRiFastFireShip ResearchItemRiGalleon ResearchItemRiHeavyDemolitionShip ResearchItemRiShipwright ResearchItemRiWarGalley ResearchItemRiBowSaw ResearchItemRiDoubleBitAxe ResearchItemRiTwoManSaw ResearchItemRiBanking ResearchItemRiCaravan ResearchItemRiCartography ResearchItemRiCoinage ResearchItemRiGuilds ResearchItemRiCropRotation ResearchItemRiHeavyPlow ResearchItemRiHorseCollar ResearchItemRiGoldMining ResearchItemRiGoldShaftMining ResearchItemRiStoneMining ResearchItemRiStoneShaftMining ResearchItemRiAtonement ResearchItemRiBlockPrinting ResearchItemRiFaith ResearchItemRiFervor ResearchItemRiHerbalMedicine ResearchItemRiHeresy ResearchItemRiIllumination ResearchItemRiRedemption ResearchItemRiSanctity ResearchItemRiTheocracy ResearchItemRiBombardCannon ResearchItemRiCappedRam ResearchItemRiHeavyScorpion ResearchItemRiOnager ResearchItemRiScorpion ResearchItemRiSiegeOnager ResearchItemRiSiegeRam ResearchItemRiBloodlines ResearchItemRiCavalier ResearchItemRiHeavyCamel ResearchItemRiHusbandry ResearchItemRiHussar ResearchItemRiLightCavalry ResearchItemRiPaladin ResearchItemRiHandCart ResearchItemRiLoom ResearchItemRiTownPatrol ResearchItemRiTownWatch ResearchItemRiWheelBarrow ResearchItemRiArchitecture ResearchItemRiBallistics ResearchItemRiBombardTower ResearchItemRiChemistry ResearchItemRiFortifiedWall ResearchItemRiGuardTower ResearchItemRiHeatedShot ResearchItemRiKeep ResearchItemRiMasonry ResearchItemRiMurderHoles ResearchItemRiSiegeEngineers ResearchItemRiStonecutting
%token StartingResourcesLowResources StartingResourcesMediumResources StartingResourcesHighResources
%token StrategicNumberSnPercentCivilianExplorers StrategicNumberSnPercentCivilianBuilders StrategicNumberSnPercentCivilianGatherers StrategicNumberSnCapCivilianExplorers StrategicNumberSnCapCivilianBuilders StrategicNumberSnCapCivilianGatherers StrategicNumberSnMinimumAttackGroupSize StrategicNumberSnTotalNumberExplorers StrategicNumberSnPercentEnemySightedResponse StrategicNumberSnEnemySightedResponseDistance StrategicNumberSnSentryDistance StrategicNumberSnRelicReturnDistance StrategicNumberSnMinimumDefendGroupSize StrategicNumberSnMaximumAttackGroupSize StrategicNumberSnMaximumDefendGroupSize StrategicNumberSnMinimumPeaceLikeLevel StrategicNumberSnPercentExplorationRequired StrategicNumberSnZeroPriorityDistance StrategicNumberSnMinimumCivilianExplorers StrategicNumberSnNumberAttackGroups StrategicNumberSnNumberDefendGroups StrategicNumberSnAttackGroupGatherSpacing StrategicNumberSnNumberExploreGroups StrategicNumberSnMinimumExploreGroupSize StrategicNumberSnMaximumExploreGroupSize StrategicNumberSnGoldDefendPriority StrategicNumberSnStoneDefendPriority StrategicNumberSnForageDefendPriority StrategicNumberSnRelicDefendPriority StrategicNumberSnTownDefendPriority StrategicNumberSnDefenseDistance StrategicNumberSnNumberBoatAttackGroups StrategicNumberSnMinimumBoatAttackGroupSize StrategicNumberSnMaximumBoatAttackGroupSize StrategicNumberSnNumberBoatExploreGroups StrategicNumberSnMinimumBoatExploreGroupSize StrategicNumberSnMaximumBoatExploreGroupSize StrategicNumberSnNumberBoatDefendGroups StrategicNumberSnMinimumBoatDefendGroupSize StrategicNumberSnMaximumBoatDefendGroupSize StrategicNumberSnDockDefendPriority StrategicNumberSnSentryDistanceVariation StrategicNumberSnMinimumTownSize StrategicNumberSnMaximumTownSize StrategicNumberSnGroupCommanderSelectionMethod StrategicNumberSnConsecutiveIdleUnitLimit StrategicNumberSnTargetEvaluationDistance StrategicNumberSnTargetEvaluationHitpoints StrategicNumberSnTargetEvaluationDamageCapability StrategicNumberSnTargetEvaluationKills StrategicNumberSnTargetEvaluationAllyProximity StrategicNumberSnTargetEvaluationRof StrategicNumberSnTargetEvaluationRandomness StrategicNumberSnCampMaxDistance StrategicNumberSnMillMaxDistance StrategicNumberSnTargetEvaluationAttackAttempts StrategicNumberSnTargetEvaluationRange StrategicNumberSnDefendOverlapDistance StrategicNumberSnScaleMinimumAttackGroupSize StrategicNumberSnScaleMaximumAttackGroupSize StrategicNumberSnAttackGroupSizeRandomness StrategicNumberSnScalingFrequency StrategicNumberSnMaximumGaiaAttackResponse StrategicNumberSnBuildFrequency StrategicNumberSnAttackSeparationTimeRandomness StrategicNumberSnAttackIntelligence StrategicNumberSnInitialAttackDelay StrategicNumberSnSaveScenarioInformation StrategicNumberSnSpecialAttackType1 StrategicNumberSnSpecialAttackInfluence1 StrategicNumberSnMinimumWaterBodySizeForDock StrategicNumberSnNumberBuildAttemptsBeforeSkip StrategicNumberSnMaxSkipsPerAttempt StrategicNumberSnFoodGathererPercentage StrategicNumberSnGoldGathererPercentage StrategicNumberSnStoneGathererPercentage StrategicNumberSnWoodGathererPercentage StrategicNumberSnTargetEvaluationContinent StrategicNumberSnTargetEvaluationSiegeWeapon StrategicNumberSnGroupLeaderDefenseDistance StrategicNumberSnInitialAttackDelayType StrategicNumberSnBlotExplorationMap StrategicNumberSnBlotSize StrategicNumberSnIntelligentGathering StrategicNumberSnTaskUngroupedSoldiers StrategicNumberSnTargetEvaluationBoat StrategicNumberSnNumberEnemyObjectsRequired StrategicNumberSnNumberMaxSkipCycles StrategicNumberSnRetaskGatherAmount StrategicNumberSnMaxRetaskGatherAmount StrategicNumberSnMaxBuildPlanGathererPercentage StrategicNumberSnFoodDropsiteDistance StrategicNumberSnWoodDropsiteDistance StrategicNumberSnStoneDropsiteDistance StrategicNumberSnGoldDropsiteDistance StrategicNumberSnInitialExplorationRequired StrategicNumberSnRandomPlacementFactor StrategicNumberSnRequiredForestTiles StrategicNumberSnAttackDiplomacyImpact StrategicNumberSnPercentHalfExploration StrategicNumberSnTargetEvaluationTimeKillRatio StrategicNumberSnTargetEvaluationInProgress StrategicNumberSnAttackWinningPlayer StrategicNumberSnCoopShareInformation StrategicNumberSnAttackWinningPlayerFactor StrategicNumberSnCoopShareAttacking StrategicNumberSnCoopShareAttackingInterval StrategicNumberSnPercentageExploreExterminators StrategicNumberSnTrackPlayerHistory StrategicNumberSnMinimumDropsiteBuffer StrategicNumberSnUseByTypeMaxGathering StrategicNumberSnMinimumBoarHuntGroupSize StrategicNumberSnMinimumAmountForTrading StrategicNumberSnEasiestReactionPercentage StrategicNumberSnEasierReactionPercentage StrategicNumberSnHitsBeforeAllianceChange StrategicNumberSnAllowCivilianDefense StrategicNumberSnNumberForwardBuilders StrategicNumberSnPercentAttackSoldiers StrategicNumberSnPercentAttackBoats StrategicNumberSnDoNotScaleForDifficultyLevel StrategicNumberSnGroupFormDistance StrategicNumberSnIgnoreAttackGroupUnderAttack StrategicNumberSnGatherDefenseUnits StrategicNumberSnMaximumWoodDropDistance StrategicNumberSnMaximumFoodDropDistance StrategicNumberSnMaximumHuntDropDistance StrategicNumberSnMaximumFishBoatDropDistance StrategicNumberSnMaximumGoldDropDistance StrategicNumberSnMaximumStoneDropDistance StrategicNumberSnGatherIdleSoldiersAtCenter StrategicNumberSnGarrisonRams
%token UnitArbalest UnitArcher UnitCavalryArcher UnitCrossbowman UnitEliteSkirmisher UnitHandCannoneer UnitHeavyCavalryArcher UnitSkirmisher UnitChampion UnitEagleWarrior UnitEliteEagleWarrior UnitHalberdier UnitLongSwordsman UnitManAtArms UnitMilitiaman UnitPikeman UnitSpearman UnitTwoHandedSwordsman UnitBerserk UnitCataphract UnitChuKoNu UnitConquistador UnitEliteBerserk UnitEliteCataphract UnitEliteChuKoNu UnitEliteConquistador UnitEliteHuskarl UnitEliteJaguarWarrior UnitEliteJanissary UnitEliteLongbowman UnitEliteMameluke UnitEliteMangudai UnitElitePlumedArcher UnitEliteSamurai UnitEliteTarkan UnitEliteTeutonicKnight UnitEliteThrowingAxeman UnitEliteWarElephant UnitEliteWarWagon UnitEliteWoadRaider UnitHuskarl UnitJaguarWarrior UnitJanissary UnitLongbowman UnitMameluke UnitMangudai UnitPetard UnitPlumedArcher UnitSamurai UnitTarkan UnitTeutonicKnight UnitThrowingAxeman UnitTrebuchet UnitWarElephant UnitWarWagon UnitWoadRaider UnitCannonGalleon UnitDemolitionShip UnitEliteCannonGalleon UnitEliteLongboat UnitEliteTurtleShip UnitFastFireShip UnitFireShip UnitFishingShip UnitGalleon UnitGalley UnitHeavyDemolitionShip UnitLongboat UnitTradeCog UnitTransportShip UnitTurtleShip UnitWarGalley UnitTradeCart UnitMissionary UnitMonk UnitBatteringRam UnitBombardCannon UnitCappedRam UnitHeavyScorpion UnitMangonel UnitOnager UnitScorpion UnitSiegeOnager UnitSiegeRam UnitCamel UnitCavalier UnitHeavyCamel UnitHussar UnitKnight UnitLightCavalry UnitPaladin UnitScoutCavalry UnitVillager UnitArcherLine UnitCavalryArcherLine UnitSkirmisherLine UnitEagleWarriorLine UnitMilitiamanLine UnitSpearmanLine UnitBerserkLine UnitCataphractLine UnitChuKoNuLine UnitConquistadorLine UnitHuskarlLine UnitJaguarWarriorLine UnitJanissaryLine UnitLongbowmanLine UnitMamelukeLine UnitMangudaiLine UnitPlumedArcherLine UnitSamuraiLine UnitTarkanLine UnitTeutonicKnightLine UnitThrowingAxemanLine UnitWarElephantLine UnitWarWagonLine UnitWoadRaiderLine UnitCannonGalleonLine UnitDemolitionShipLine UnitFireShipLine UnitGalleyLine UnitLongboatLine UnitTurtleShipLine UnitBatteringRamLine UnitMangonelLine UnitScorpionLine UnitCamelLine UnitKnightLine UnitScoutCavalryLine
%token VictoryConditionStandard VictoryConditionConquest VictoryConditionTimeLimit VictoryConditionScore VictoryConditionCustom
%token WallTypeFortifiedWall WallTypePalisadeWall WallTypeStoneWall WallTypeStoneWallLine
%token DoNothing
%token AcknowledgeEvent
%token AcknowledgeTaunt
%token AttackNow
%token Build
%token BuildForward
%token BuildGate
%token BuildWall
%token BuyCommodity
%token CcAddResource
%token ChatLocal
%token ChatLocalUsingId
%token ChatLocalUsingRange
%token ChatLocalToSelf
%token ChatToAll
%token ChatToAllUsingId
%token ChatToAllUsingRange
%token ChatToAllies
%token ChatToAlliesUsingId
%token ChatToAlliesUsingRange
%token ChatToEnemies
%token ChatToEnemiesUsingId
%token ChatToEnemiesUsingRange
%token ChatToPlayer
%token ChatToPlayerUsingId
%token ChatToPlayerUsingRange
%token ChatTrace
%token ClearTributeMemory
%token DeleteBuilding
%token DeleteUnit
%token DisableSelf
%token DisableTimer
%token EnableTimer
%token EnableWallPlacement
%token GenerateRandomNumber
%token Log
%token LogTrace
%token ReleaseEscrow
%token Research
%token Resign
%token SellCommodity
%token SetDifficultyParameter
%token SetDoctrine
%token SetEscrowPercentage
%token SetGoal
%token SetSharedGoal
%token SetSignal
%token SetStance
%token SetStrategicNumber
%token Spy
%token Taunt
%token TauntUsingRange
%token Train
%token TributeToPlayer
%%

aiscript:
    /* Empty */
    | rules { printf("got script\n"); }
;

rules:
    rule { printf("got single rule\n"); }
    | rule rules { printf("got multiple rules\n"); }

rule:
    OpenParen RuleStart conditions ConditionActionSeparator actions CloseParen { printf("got rule\n====\n\n"); }

conditions:
    condition {  printf("got single condition\n"); }
    | condition conditions {  printf("got multiple conditions\n"); }

condition:
    OpenParen Not condition CloseParen {}//  printf("got negated condition\n"); }
    | OpenParen Or conditions CloseParen { }// printf("got multiple or conditions\n"); }
    | OpenParen symbolname CloseParen {}//  printf("got condition with symbol '%s'\n", $2); }
    | OpenParen symbolname Number CloseParen {}//  printf("got condition with symbol '%s' and number %d\n", $2, $3); }
    | OpenParen symbolname Number Number CloseParen {}//  printf("got condition with symbol '%s' and numbers %d %d\n", $2, $3, $4); }
    | OpenParen symbolname symbolname CloseParen {}//  printf("got condition with two symbols '%s' %s\n", $2, $3); }
    | OpenParen symbolname symbolname symbolname CloseParen {}//  printf("got condition with three symbols %s %s %s\n", $2, $3, $4); }
    | OpenParen symbolname comparison Number CloseParen {}//  printf("got condition with comparison %s %d\n", $2, $4); }
    | OpenParen symbolname comparison symbolname CloseParen {}//  printf("got condition with comparison %s %s\n", $2, $4); }
    | OpenParen symbolname symbolname comparison symbolname CloseParen {}//  printf("got condition with comparison %s %s %s\n", $2, $3, $5); }
    | OpenParen symbolname symbolname comparison Number CloseParen {}//  printf("got condition with comparison %s %s %d\n", $2, $3, $5); }
    | OpenParen symbolname symbolname symbolname comparison Number CloseParen {}//  printf("got condition with comparison %s %s %s %d\n", $2, $3, $4, $6); }
//condition:
//    OpenParen Not condition CloseParen {  printf("got negated condition\n"); }
//    | OpenParen Or conditions CloseParen {  printf("got multiple or conditions\n"); }
//    | OpenParen SymbolName CloseParen {  printf("got condition with symbol '%s'\n", $2); }
//    | OpenParen SymbolName Number CloseParen {  printf("got condition with symbol '%s' and number %d\n", $2, $3); }
//    | OpenParen SymbolName Number Number CloseParen {  printf("got condition with symbol '%s' and numbers %d %d\n", $2, $3, $4); }
//    | OpenParen SymbolName SymbolName CloseParen {  printf("got condition with two symbols '%s' %s\n", $2, $3); }
//    | OpenParen SymbolName SymbolName SymbolName CloseParen {  printf("got condition with three symbols %s %s %s\n", $2, $3, $4); }
//    | OpenParen SymbolName comparison Number CloseParen {  printf("got condition with comparison %s %d\n", $2, $4); }
//    | OpenParen SymbolName comparison SymbolName CloseParen {  printf("got condition with comparison %s %s\n", $2, $4); }
//    | OpenParen SymbolName SymbolName comparison SymbolName CloseParen {  printf("got condition with comparison %s %s %s\n", $2, $3, $5); }
//    | OpenParen SymbolName SymbolName comparison Number CloseParen {  printf("got condition with comparison %s %s %d\n", $2, $3, $5); }
//    | OpenParen SymbolName SymbolName SymbolName comparison Number CloseParen {  printf("got condition with comparison %s %s %s %d\n", $2, $3, $4, $6); }


comparison:
    RelOpLessThan {  printf("got lessthan\n"); }
    | RelOpLessOrEqual {  printf("got lessorequal\n"); }
    | RelOpGreaterThan {  printf("got greaterthan\n"); }
    | RelOpGreaterOrEqual {  printf("got greaterorequal\n"); }
    | RelOpEqual {  printf("got equals\n"); }

actions:
    OpenParen action CloseParen {  printf("got single action\n"); }
    | action actions {  printf("got multiple actions\n"); }

//action:
//    OpenParen SymbolName CloseParen { printf("got action %s without arguments\n", $2); }
//    | OpenParen SymbolName String CloseParen {  printf("got action %s with string %s\n", $2, $3); }
//    | OpenParen SymbolName SymbolName Number CloseParen {  printf("got action %s with symbol %s and number %d\n", $2, $3, $4); }
//    | OpenParen SymbolName SymbolName CloseParen {  printf("got action %s with symbol %s\n", $2, $3); }
//    | OpenParen SymbolName Number CloseParen {  printf("got action %s with number %d\n", $2, $3); }
//    | OpenParen SymbolName Number Number CloseParen {  printf("got action %s with numbers %d %d\n", $2, $3, $4); }
//
age:
    AgeDarkAge  {}// static_cast<Condition*>(aiRule)->type = Age::DarkAge; } 
  | AgeFeudalAge  {}// static_cast<Condition*>(aiRule)->type = Age::FeudalAge; } 
  | AgeCastleAge  {}// static_cast<Condition*>(aiRule)->type = Age::CastleAge; } 
  | AgeImperialAge  {}// static_cast<Condition*>(aiRule)->type = Age::ImperialAge; } 
  | AgePostImperialAge  {}// static_cast<Condition*>(aiRule)->type = Age::PostImperialAge; } 

building:
    BuildingArcheryRange  {}// static_cast<Condition*>(aiRule)->type = Building::ArcheryRange; } 
  | BuildingBarracks  {}// static_cast<Condition*>(aiRule)->type = Building::Barracks; } 
  | BuildingBlacksmith  {}// static_cast<Condition*>(aiRule)->type = Building::Blacksmith; } 
  | BuildingBombardTower  {}// static_cast<Condition*>(aiRule)->type = Building::BombardTower; } 
  | BuildingCastle  {}// static_cast<Condition*>(aiRule)->type = Building::Castle; } 
  | BuildingDock  {}// static_cast<Condition*>(aiRule)->type = Building::Dock; } 
  | BuildingFarm  {}// static_cast<Condition*>(aiRule)->type = Building::Farm; } 
  | BuildingFishTrap  {}// static_cast<Condition*>(aiRule)->type = Building::FishTrap; } 
  | BuildingGuardTower  {}// static_cast<Condition*>(aiRule)->type = Building::GuardTower; } 
  | BuildingHouse  {}// static_cast<Condition*>(aiRule)->type = Building::House; } 
  | BuildingKeep  {}// static_cast<Condition*>(aiRule)->type = Building::Keep; } 
  | BuildingLumberCamp  {}// static_cast<Condition*>(aiRule)->type = Building::LumberCamp; } 
  | BuildingMarket  {}// static_cast<Condition*>(aiRule)->type = Building::Market; } 
  | BuildingMill  {}// static_cast<Condition*>(aiRule)->type = Building::Mill; } 
  | BuildingMiningCamp  {}// static_cast<Condition*>(aiRule)->type = Building::MiningCamp; } 
  | BuildingMonastery  {}// static_cast<Condition*>(aiRule)->type = Building::Monastery; } 
  | BuildingOutpost  {}// static_cast<Condition*>(aiRule)->type = Building::Outpost; } 
  | BuildingSiegeWorkshop  {}// static_cast<Condition*>(aiRule)->type = Building::SiegeWorkshop; } 
  | BuildingStable  {}// static_cast<Condition*>(aiRule)->type = Building::Stable; } 
  | BuildingTownCenter  {}// static_cast<Condition*>(aiRule)->type = Building::TownCenter; } 
  | BuildingUniversity  {}// static_cast<Condition*>(aiRule)->type = Building::University; } 
  | BuildingWatchTower  {}// static_cast<Condition*>(aiRule)->type = Building::WatchTower; } 
  | BuildingWonder  {}// static_cast<Condition*>(aiRule)->type = Building::Wonder; } 
  | BuildingWatchTowerLine  {}// static_cast<Condition*>(aiRule)->type = Building::WatchTowerLine; } 

civ:
    CivBriton  {}// static_cast<Condition*>(aiRule)->type = Civ::Briton; } 
  | CivByzantine  {}// static_cast<Condition*>(aiRule)->type = Civ::Byzantine; } 
  | CivCeltic  {}// static_cast<Condition*>(aiRule)->type = Civ::Celtic; } 
  | CivChinese  {}// static_cast<Condition*>(aiRule)->type = Civ::Chinese; } 
  | CivFrankish  {}// static_cast<Condition*>(aiRule)->type = Civ::Frankish; } 
  | CivGothic  {}// static_cast<Condition*>(aiRule)->type = Civ::Gothic; } 
  | CivJapanese  {}// static_cast<Condition*>(aiRule)->type = Civ::Japanese; } 
  | CivMongol  {}// static_cast<Condition*>(aiRule)->type = Civ::Mongol; } 
  | CivPersian  {}// static_cast<Condition*>(aiRule)->type = Civ::Persian; } 
  | CivSaracen  {}// static_cast<Condition*>(aiRule)->type = Civ::Saracen; } 
  | CivTeutonic  {}// static_cast<Condition*>(aiRule)->type = Civ::Teutonic; } 
  | CivTurkish  {}// static_cast<Condition*>(aiRule)->type = Civ::Turkish; } 
  | CivViking  {}// static_cast<Condition*>(aiRule)->type = Civ::Viking; } 

commodity:
    CommodityFood  {}// static_cast<Condition*>(aiRule)->type = Commodity::Food; } 
  | CommodityStone  {}// static_cast<Condition*>(aiRule)->type = Commodity::Stone; } 
  | CommodityWood  {}// static_cast<Condition*>(aiRule)->type = Commodity::Wood; } 
  | CommodityGold  {}// static_cast<Condition*>(aiRule)->type = Commodity::Gold; } 

difficulty:
    DifficultyEasiest  {}// static_cast<Condition*>(aiRule)->type = Difficulty::Easiest; } 
  | DifficultyEasy  {}// static_cast<Condition*>(aiRule)->type = Difficulty::Easy; } 
  | DifficultyModerate  {}// static_cast<Condition*>(aiRule)->type = Difficulty::Moderate; } 
  | DifficultyHard  {}// static_cast<Condition*>(aiRule)->type = Difficulty::Hard; } 
  | DifficultyHardest  {}// static_cast<Condition*>(aiRule)->type = Difficulty::Hardest; } 

difficultyparameter:
    DifficultyParameterAbilityToDodgeMissiles  {}// static_cast<Condition*>(aiRule)->type = DifficultyParameter::AbilityToDodgeMissiles; } 
  | DifficultyParameterAbilityToMaintainDistance  {}// static_cast<Condition*>(aiRule)->type = DifficultyParameter::AbilityToMaintainDistance; } 

diplomaticstance:
    DiplomaticStanceAlly  {}// static_cast<Condition*>(aiRule)->type = DiplomaticStance::Ally; } 
  | DiplomaticStanceNeutral  {}// static_cast<Condition*>(aiRule)->type = DiplomaticStance::Neutral; } 
  | DiplomaticStanceEnemy  {}// static_cast<Condition*>(aiRule)->type = DiplomaticStance::Enemy; } 

eventid:
    Number
eventtype:
    EventTypeTrigger  {}// static_cast<Condition*>(aiRule)->type = EventType::Trigger; } 

goalid:
    Number
mapsize:
    MapSizeTiny  {}// static_cast<Condition*>(aiRule)->type = MapSize::Tiny; } 
  | MapSizeSmall  {}// static_cast<Condition*>(aiRule)->type = MapSize::Small; } 
  | MapSizeMedium  {}// static_cast<Condition*>(aiRule)->type = MapSize::Medium; } 
  | MapSizeNormal  {}// static_cast<Condition*>(aiRule)->type = MapSize::Normal; } 
  | MapSizeLarge  {}// static_cast<Condition*>(aiRule)->type = MapSize::Large; } 
  | MapSizeGiant  {}// static_cast<Condition*>(aiRule)->type = MapSize::Giant; } 

maptype:
    MapTypeArabia  {}// static_cast<Condition*>(aiRule)->type = MapType::Arabia; } 
  | MapTypeArchipelago  {}// static_cast<Condition*>(aiRule)->type = MapType::Archipelago; } 
  | MapTypeBaltic  {}// static_cast<Condition*>(aiRule)->type = MapType::Baltic; } 
  | MapTypeBlackForest  {}// static_cast<Condition*>(aiRule)->type = MapType::BlackForest; } 
  | MapTypeCoastal  {}// static_cast<Condition*>(aiRule)->type = MapType::Coastal; } 
  | MapTypeContinental  {}// static_cast<Condition*>(aiRule)->type = MapType::Continental; } 
  | MapTypeCraterLake  {}// static_cast<Condition*>(aiRule)->type = MapType::CraterLake; } 
  | MapTypeFortress  {}// static_cast<Condition*>(aiRule)->type = MapType::Fortress; } 
  | MapTypeGoldRush  {}// static_cast<Condition*>(aiRule)->type = MapType::GoldRush; } 
  | MapTypeHighland  {}// static_cast<Condition*>(aiRule)->type = MapType::Highland; } 
  | MapTypeIslands  {}// static_cast<Condition*>(aiRule)->type = MapType::Islands; } 
  | MapTypeMediterranean  {}// static_cast<Condition*>(aiRule)->type = MapType::Mediterranean; } 
  | MapTypeMigration  {}// static_cast<Condition*>(aiRule)->type = MapType::Migration; } 
  | MapTypeRivers  {}// static_cast<Condition*>(aiRule)->type = MapType::Rivers; } 
  | MapTypeTeamIslands  {}// static_cast<Condition*>(aiRule)->type = MapType::TeamIslands; } 
  | MapTypeScenarioMap  {}// static_cast<Condition*>(aiRule)->type = MapType::ScenarioMap; } 

perimeter:
    Number
playernumber:
    PlayerNumberAnyAlly  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyAlly; } 
  | PlayerNumberAnyComputer  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyComputer; } 
  | PlayerNumberAnyComputerAlly  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyComputerAlly; } 
  | PlayerNumberAnyComputerEnemy  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyComputerEnemy; } 
  | PlayerNumberAnyComputerNeutral  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyComputerNeutral; } 
  | PlayerNumberAnyEnemy  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyEnemy; } 
  | PlayerNumberAnyHuman  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyHuman; } 
  | PlayerNumberAnyHumanAlly  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyHumanAlly; } 
  | PlayerNumberAnyHumanEnemy  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyHumanEnemy; } 
  | PlayerNumberAnyHumanNeutral  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyHumanNeutral; } 
  | PlayerNumberAnyNeutral  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::AnyNeutral; } 
  | PlayerNumberEveryAlly  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::EveryAlly; } 
  | PlayerNumberEveryComputer  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::EveryComputer; } 
  | PlayerNumberEveryEnemy  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::EveryEnemy; } 
  | PlayerNumberEveryHuman  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::EveryHuman; } 
  | PlayerNumberEveryNeutral  {}// static_cast<Condition*>(aiRule)->type = PlayerNumber::EveryNeutral; } 

relop:
    RelOpLessThan  {}// static_cast<Condition*>(aiRule)->type = RelOp::LessThan; } 
  | RelOpLessOrEqual  {}// static_cast<Condition*>(aiRule)->type = RelOp::LessOrEqual; } 
  | RelOpGreaterThan  {}// static_cast<Condition*>(aiRule)->type = RelOp::GreaterThan; } 
  | RelOpGreaterOrEqual  {}// static_cast<Condition*>(aiRule)->type = RelOp::GreaterOrEqual; } 
  | RelOpEqual  {}// static_cast<Condition*>(aiRule)->type = RelOp::Equal; } 
  | RelOpNotEqual  {}// static_cast<Condition*>(aiRule)->type = RelOp::NotEqual; } 

researchitem:
    ResearchItemRiArbalest  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiArbalest; } 
  | ResearchItemRiCrossbow  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiCrossbow; } 
  | ResearchItemRiEliteSkirmisher  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteSkirmisher; } 
  | ResearchItemRiHandCannon  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHandCannon; } 
  | ResearchItemRiHeavyCavalryArcher  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHeavyCavalryArcher; } 
  | ResearchItemRiChampion  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiChampion; } 
  | ResearchItemRiEliteEagleWarrior  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteEagleWarrior; } 
  | ResearchItemRiHalberdier  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHalberdier; } 
  | ResearchItemRiLongSwordsman  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiLongSwordsman; } 
  | ResearchItemRiManAtArms  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiManAtArms; } 
  | ResearchItemRiParthianTactics  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiParthianTactics; } 
  | ResearchItemRiPikeman  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiPikeman; } 
  | ResearchItemRiSquires  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiSquires; } 
  | ResearchItemRiThumbRing  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiThumbRing; } 
  | ResearchItemRiTracking  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiTracking; } 
  | ResearchItemRiTwoHandedSwordsman  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiTwoHandedSwordsman; } 
  | ResearchItemRiBlastFurnace  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiBlastFurnace; } 
  | ResearchItemRiBodkinArrow  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiBodkinArrow; } 
  | ResearchItemRiBracer  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiBracer; } 
  | ResearchItemRiChainBarding  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiChainBarding; } 
  | ResearchItemRiChainMail  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiChainMail; } 
  | ResearchItemRiFletching  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiFletching; } 
  | ResearchItemRiForging  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiForging; } 
  | ResearchItemRiIronCasting  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiIronCasting; } 
  | ResearchItemRiLeatherArcherArmor  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiLeatherArcherArmor; } 
  | ResearchItemRiPaddedArcherArmor  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiPaddedArcherArmor; } 
  | ResearchItemRiPlateBarding  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiPlateBarding; } 
  | ResearchItemRiPlateMail  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiPlateMail; } 
  | ResearchItemRiRingArcherArmor  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiRingArcherArmor; } 
  | ResearchItemRiScaleBarding  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiScaleBarding; } 
  | ResearchItemRiScaleMail  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiScaleMail; } 
  | ResearchItemRiConscription  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiConscription; } 
  | ResearchItemRiHoardings  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHoardings; } 
  | ResearchItemRiSappers  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiSappers; } 
  | ResearchItemRiEliteBerserk  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteBerserk; } 
  | ResearchItemRiEliteCataphract  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteCataphract; } 
  | ResearchItemRiEliteChuKoNu  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteChuKoNu; } 
  | ResearchItemRiEliteHuskarl  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteHuskarl; } 
  | ResearchItemRiEliteJanissary  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteJanissary; } 
  | ResearchItemRiEliteLongbowman  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteLongbowman; } 
  | ResearchItemRiEliteMameluke  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteMameluke; } 
  | ResearchItemRiEliteMangudai  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteMangudai; } 
  | ResearchItemRiEliteSamurai  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteSamurai; } 
  | ResearchItemRiEliteTeutonicKnight  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteTeutonicKnight; } 
  | ResearchItemRiEliteThrowingAxeman  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteThrowingAxeman; } 
  | ResearchItemRiEliteWarElephant  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteWarElephant; } 
  | ResearchItemRiEliteWoadRaider  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteWoadRaider; } 
  | ResearchItemRiMyUniqueEliteUnit  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiMyUniqueEliteUnit; } 
  | ResearchItemRiMyUniqueResearch  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiMyUniqueResearch; } 
  | ResearchItemRiCannonGalleon  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiCannonGalleon; } 
  | ResearchItemRiCareening  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiCareening; } 
  | ResearchItemRiDeckGuns  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiDeckGuns; } 
  | ResearchItemRiDryDock  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiDryDock; } 
  | ResearchItemRiEliteLongboat  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiEliteLongboat; } 
  | ResearchItemRiFastFireShip  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiFastFireShip; } 
  | ResearchItemRiGalleon  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiGalleon; } 
  | ResearchItemRiHeavyDemolitionShip  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHeavyDemolitionShip; } 
  | ResearchItemRiShipwright  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiShipwright; } 
  | ResearchItemRiWarGalley  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiWarGalley; } 
  | ResearchItemRiBowSaw  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiBowSaw; } 
  | ResearchItemRiDoubleBitAxe  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiDoubleBitAxe; } 
  | ResearchItemRiTwoManSaw  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiTwoManSaw; } 
  | ResearchItemRiBanking  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiBanking; } 
  | ResearchItemRiCaravan  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiCaravan; } 
  | ResearchItemRiCartography  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiCartography; } 
  | ResearchItemRiCoinage  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiCoinage; } 
  | ResearchItemRiGuilds  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiGuilds; } 
  | ResearchItemRiCropRotation  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiCropRotation; } 
  | ResearchItemRiHeavyPlow  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHeavyPlow; } 
  | ResearchItemRiHorseCollar  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHorseCollar; } 
  | ResearchItemRiGoldMining  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiGoldMining; } 
  | ResearchItemRiGoldShaftMining  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiGoldShaftMining; } 
  | ResearchItemRiStoneMining  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiStoneMining; } 
  | ResearchItemRiStoneShaftMining  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiStoneShaftMining; } 
  | ResearchItemRiAtonement  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiAtonement; } 
  | ResearchItemRiBlockPrinting  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiBlockPrinting; } 
  | ResearchItemRiFaith  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiFaith; } 
  | ResearchItemRiFervor  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiFervor; } 
  | ResearchItemRiHerbalMedicine  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHerbalMedicine; } 
  | ResearchItemRiHeresy  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHeresy; } 
  | ResearchItemRiIllumination  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiIllumination; } 
  | ResearchItemRiRedemption  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiRedemption; } 
  | ResearchItemRiSanctity  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiSanctity; } 
  | ResearchItemRiTheocracy  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiTheocracy; } 
  | ResearchItemRiBombardCannon  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiBombardCannon; } 
  | ResearchItemRiCappedRam  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiCappedRam; } 
  | ResearchItemRiHeavyScorpion  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHeavyScorpion; } 
  | ResearchItemRiOnager  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiOnager; } 
  | ResearchItemRiScorpion  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiScorpion; } 
  | ResearchItemRiSiegeOnager  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiSiegeOnager; } 
  | ResearchItemRiSiegeRam  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiSiegeRam; } 
  | ResearchItemRiBloodlines  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiBloodlines; } 
  | ResearchItemRiCavalier  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiCavalier; } 
  | ResearchItemRiHeavyCamel  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHeavyCamel; } 
  | ResearchItemRiHusbandry  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHusbandry; } 
  | ResearchItemRiHussar  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHussar; } 
  | ResearchItemRiLightCavalry  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiLightCavalry; } 
  | ResearchItemRiPaladin  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiPaladin; } 
  | ResearchItemRiHandCart  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHandCart; } 
  | ResearchItemRiLoom  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiLoom; } 
  | ResearchItemRiTownPatrol  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiTownPatrol; } 
  | ResearchItemRiTownWatch  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiTownWatch; } 
  | ResearchItemRiWheelBarrow  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiWheelBarrow; } 
  | ResearchItemRiArchitecture  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiArchitecture; } 
  | ResearchItemRiBallistics  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiBallistics; } 
  | ResearchItemRiBombardTower  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiBombardTower; } 
  | ResearchItemRiChemistry  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiChemistry; } 
  | ResearchItemRiFortifiedWall  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiFortifiedWall; } 
  | ResearchItemRiGuardTower  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiGuardTower; } 
  | ResearchItemRiHeatedShot  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiHeatedShot; } 
  | ResearchItemRiKeep  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiKeep; } 
  | ResearchItemRiMasonry  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiMasonry; } 
  | ResearchItemRiMurderHoles  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiMurderHoles; } 
  | ResearchItemRiSiegeEngineers  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiSiegeEngineers; } 
  | ResearchItemRiStonecutting  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::RiStonecutting; } 

sharedgoalid:
    Number
signalid:
    Number
startingresources:
    StartingResourcesLowResources  {}// static_cast<Condition*>(aiRule)->type = StartingResources::LowResources; } 
  | StartingResourcesMediumResources  {}// static_cast<Condition*>(aiRule)->type = StartingResources::MediumResources; } 
  | StartingResourcesHighResources  {}// static_cast<Condition*>(aiRule)->type = StartingResources::HighResources; } 

strategicnumber:
    StrategicNumberSnPercentCivilianExplorers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnPercentCivilianExplorers; } 
  | StrategicNumberSnPercentCivilianBuilders  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnPercentCivilianBuilders; } 
  | StrategicNumberSnPercentCivilianGatherers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnPercentCivilianGatherers; } 
  | StrategicNumberSnCapCivilianExplorers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnCapCivilianExplorers; } 
  | StrategicNumberSnCapCivilianBuilders  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnCapCivilianBuilders; } 
  | StrategicNumberSnCapCivilianGatherers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnCapCivilianGatherers; } 
  | StrategicNumberSnMinimumAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumAttackGroupSize; } 
  | StrategicNumberSnTotalNumberExplorers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTotalNumberExplorers; } 
  | StrategicNumberSnPercentEnemySightedResponse  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnPercentEnemySightedResponse; } 
  | StrategicNumberSnEnemySightedResponseDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnEnemySightedResponseDistance; } 
  | StrategicNumberSnSentryDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnSentryDistance; } 
  | StrategicNumberSnRelicReturnDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnRelicReturnDistance; } 
  | StrategicNumberSnMinimumDefendGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumDefendGroupSize; } 
  | StrategicNumberSnMaximumAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumAttackGroupSize; } 
  | StrategicNumberSnMaximumDefendGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumDefendGroupSize; } 
  | StrategicNumberSnMinimumPeaceLikeLevel  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumPeaceLikeLevel; } 
  | StrategicNumberSnPercentExplorationRequired  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnPercentExplorationRequired; } 
  | StrategicNumberSnZeroPriorityDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnZeroPriorityDistance; } 
  | StrategicNumberSnMinimumCivilianExplorers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumCivilianExplorers; } 
  | StrategicNumberSnNumberAttackGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnNumberAttackGroups; } 
  | StrategicNumberSnNumberDefendGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnNumberDefendGroups; } 
  | StrategicNumberSnAttackGroupGatherSpacing  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnAttackGroupGatherSpacing; } 
  | StrategicNumberSnNumberExploreGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnNumberExploreGroups; } 
  | StrategicNumberSnMinimumExploreGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumExploreGroupSize; } 
  | StrategicNumberSnMaximumExploreGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumExploreGroupSize; } 
  | StrategicNumberSnGoldDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnGoldDefendPriority; } 
  | StrategicNumberSnStoneDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnStoneDefendPriority; } 
  | StrategicNumberSnForageDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnForageDefendPriority; } 
  | StrategicNumberSnRelicDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnRelicDefendPriority; } 
  | StrategicNumberSnTownDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTownDefendPriority; } 
  | StrategicNumberSnDefenseDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnDefenseDistance; } 
  | StrategicNumberSnNumberBoatAttackGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnNumberBoatAttackGroups; } 
  | StrategicNumberSnMinimumBoatAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumBoatAttackGroupSize; } 
  | StrategicNumberSnMaximumBoatAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumBoatAttackGroupSize; } 
  | StrategicNumberSnNumberBoatExploreGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnNumberBoatExploreGroups; } 
  | StrategicNumberSnMinimumBoatExploreGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumBoatExploreGroupSize; } 
  | StrategicNumberSnMaximumBoatExploreGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumBoatExploreGroupSize; } 
  | StrategicNumberSnNumberBoatDefendGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnNumberBoatDefendGroups; } 
  | StrategicNumberSnMinimumBoatDefendGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumBoatDefendGroupSize; } 
  | StrategicNumberSnMaximumBoatDefendGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumBoatDefendGroupSize; } 
  | StrategicNumberSnDockDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnDockDefendPriority; } 
  | StrategicNumberSnSentryDistanceVariation  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnSentryDistanceVariation; } 
  | StrategicNumberSnMinimumTownSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumTownSize; } 
  | StrategicNumberSnMaximumTownSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumTownSize; } 
  | StrategicNumberSnGroupCommanderSelectionMethod  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnGroupCommanderSelectionMethod; } 
  | StrategicNumberSnConsecutiveIdleUnitLimit  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnConsecutiveIdleUnitLimit; } 
  | StrategicNumberSnTargetEvaluationDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationDistance; } 
  | StrategicNumberSnTargetEvaluationHitpoints  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationHitpoints; } 
  | StrategicNumberSnTargetEvaluationDamageCapability  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationDamageCapability; } 
  | StrategicNumberSnTargetEvaluationKills  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationKills; } 
  | StrategicNumberSnTargetEvaluationAllyProximity  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationAllyProximity; } 
  | StrategicNumberSnTargetEvaluationRof  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationRof; } 
  | StrategicNumberSnTargetEvaluationRandomness  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationRandomness; } 
  | StrategicNumberSnCampMaxDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnCampMaxDistance; } 
  | StrategicNumberSnMillMaxDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMillMaxDistance; } 
  | StrategicNumberSnTargetEvaluationAttackAttempts  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationAttackAttempts; } 
  | StrategicNumberSnTargetEvaluationRange  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationRange; } 
  | StrategicNumberSnDefendOverlapDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnDefendOverlapDistance; } 
  | StrategicNumberSnScaleMinimumAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnScaleMinimumAttackGroupSize; } 
  | StrategicNumberSnScaleMaximumAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnScaleMaximumAttackGroupSize; } 
  | StrategicNumberSnAttackGroupSizeRandomness  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnAttackGroupSizeRandomness; } 
  | StrategicNumberSnScalingFrequency  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnScalingFrequency; } 
  | StrategicNumberSnMaximumGaiaAttackResponse  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumGaiaAttackResponse; } 
  | StrategicNumberSnBuildFrequency  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnBuildFrequency; } 
  | StrategicNumberSnAttackSeparationTimeRandomness  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnAttackSeparationTimeRandomness; } 
  | StrategicNumberSnAttackIntelligence  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnAttackIntelligence; } 
  | StrategicNumberSnInitialAttackDelay  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnInitialAttackDelay; } 
  | StrategicNumberSnSaveScenarioInformation  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnSaveScenarioInformation; } 
  | StrategicNumberSnSpecialAttackType1  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnSpecialAttackType1; } 
  | StrategicNumberSnSpecialAttackInfluence1  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnSpecialAttackInfluence1; } 
  | StrategicNumberSnMinimumWaterBodySizeForDock  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumWaterBodySizeForDock; } 
  | StrategicNumberSnNumberBuildAttemptsBeforeSkip  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnNumberBuildAttemptsBeforeSkip; } 
  | StrategicNumberSnMaxSkipsPerAttempt  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaxSkipsPerAttempt; } 
  | StrategicNumberSnFoodGathererPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnFoodGathererPercentage; } 
  | StrategicNumberSnGoldGathererPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnGoldGathererPercentage; } 
  | StrategicNumberSnStoneGathererPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnStoneGathererPercentage; } 
  | StrategicNumberSnWoodGathererPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnWoodGathererPercentage; } 
  | StrategicNumberSnTargetEvaluationContinent  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationContinent; } 
  | StrategicNumberSnTargetEvaluationSiegeWeapon  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationSiegeWeapon; } 
  | StrategicNumberSnGroupLeaderDefenseDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnGroupLeaderDefenseDistance; } 
  | StrategicNumberSnInitialAttackDelayType  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnInitialAttackDelayType; } 
  | StrategicNumberSnBlotExplorationMap  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnBlotExplorationMap; } 
  | StrategicNumberSnBlotSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnBlotSize; } 
  | StrategicNumberSnIntelligentGathering  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnIntelligentGathering; } 
  | StrategicNumberSnTaskUngroupedSoldiers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTaskUngroupedSoldiers; } 
  | StrategicNumberSnTargetEvaluationBoat  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationBoat; } 
  | StrategicNumberSnNumberEnemyObjectsRequired  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnNumberEnemyObjectsRequired; } 
  | StrategicNumberSnNumberMaxSkipCycles  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnNumberMaxSkipCycles; } 
  | StrategicNumberSnRetaskGatherAmount  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnRetaskGatherAmount; } 
  | StrategicNumberSnMaxRetaskGatherAmount  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaxRetaskGatherAmount; } 
  | StrategicNumberSnMaxBuildPlanGathererPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaxBuildPlanGathererPercentage; } 
  | StrategicNumberSnFoodDropsiteDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnFoodDropsiteDistance; } 
  | StrategicNumberSnWoodDropsiteDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnWoodDropsiteDistance; } 
  | StrategicNumberSnStoneDropsiteDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnStoneDropsiteDistance; } 
  | StrategicNumberSnGoldDropsiteDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnGoldDropsiteDistance; } 
  | StrategicNumberSnInitialExplorationRequired  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnInitialExplorationRequired; } 
  | StrategicNumberSnRandomPlacementFactor  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnRandomPlacementFactor; } 
  | StrategicNumberSnRequiredForestTiles  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnRequiredForestTiles; } 
  | StrategicNumberSnAttackDiplomacyImpact  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnAttackDiplomacyImpact; } 
  | StrategicNumberSnPercentHalfExploration  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnPercentHalfExploration; } 
  | StrategicNumberSnTargetEvaluationTimeKillRatio  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationTimeKillRatio; } 
  | StrategicNumberSnTargetEvaluationInProgress  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTargetEvaluationInProgress; } 
  | StrategicNumberSnAttackWinningPlayer  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnAttackWinningPlayer; } 
  | StrategicNumberSnCoopShareInformation  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnCoopShareInformation; } 
  | StrategicNumberSnAttackWinningPlayerFactor  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnAttackWinningPlayerFactor; } 
  | StrategicNumberSnCoopShareAttacking  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnCoopShareAttacking; } 
  | StrategicNumberSnCoopShareAttackingInterval  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnCoopShareAttackingInterval; } 
  | StrategicNumberSnPercentageExploreExterminators  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnPercentageExploreExterminators; } 
  | StrategicNumberSnTrackPlayerHistory  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnTrackPlayerHistory; } 
  | StrategicNumberSnMinimumDropsiteBuffer  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumDropsiteBuffer; } 
  | StrategicNumberSnUseByTypeMaxGathering  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnUseByTypeMaxGathering; } 
  | StrategicNumberSnMinimumBoarHuntGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumBoarHuntGroupSize; } 
  | StrategicNumberSnMinimumAmountForTrading  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMinimumAmountForTrading; } 
  | StrategicNumberSnEasiestReactionPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnEasiestReactionPercentage; } 
  | StrategicNumberSnEasierReactionPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnEasierReactionPercentage; } 
  | StrategicNumberSnHitsBeforeAllianceChange  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnHitsBeforeAllianceChange; } 
  | StrategicNumberSnAllowCivilianDefense  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnAllowCivilianDefense; } 
  | StrategicNumberSnNumberForwardBuilders  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnNumberForwardBuilders; } 
  | StrategicNumberSnPercentAttackSoldiers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnPercentAttackSoldiers; } 
  | StrategicNumberSnPercentAttackBoats  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnPercentAttackBoats; } 
  | StrategicNumberSnDoNotScaleForDifficultyLevel  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnDoNotScaleForDifficultyLevel; } 
  | StrategicNumberSnGroupFormDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnGroupFormDistance; } 
  | StrategicNumberSnIgnoreAttackGroupUnderAttack  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnIgnoreAttackGroupUnderAttack; } 
  | StrategicNumberSnGatherDefenseUnits  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnGatherDefenseUnits; } 
  | StrategicNumberSnMaximumWoodDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumWoodDropDistance; } 
  | StrategicNumberSnMaximumFoodDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumFoodDropDistance; } 
  | StrategicNumberSnMaximumHuntDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumHuntDropDistance; } 
  | StrategicNumberSnMaximumFishBoatDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumFishBoatDropDistance; } 
  | StrategicNumberSnMaximumGoldDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumGoldDropDistance; } 
  | StrategicNumberSnMaximumStoneDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnMaximumStoneDropDistance; } 
  | StrategicNumberSnGatherIdleSoldiersAtCenter  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnGatherIdleSoldiersAtCenter; } 
  | StrategicNumberSnGarrisonRams  {}// static_cast<Condition*>(aiRule)->type = StrategicNumber::SnGarrisonRams; } 

stringid:
    Number
stringidrange:
    Number
stringidstart:
    Number
tauntid:
    Number
tauntrange:
    Number
tauntstart:
    Number
timerid:
    Number
unit:
    UnitArbalest  {}// static_cast<Condition*>(aiRule)->type = Unit::Arbalest; } 
  | UnitArcher  {}// static_cast<Condition*>(aiRule)->type = Unit::Archer; } 
  | UnitCavalryArcher  {}// static_cast<Condition*>(aiRule)->type = Unit::CavalryArcher; } 
  | UnitCrossbowman  {}// static_cast<Condition*>(aiRule)->type = Unit::Crossbowman; } 
  | UnitEliteSkirmisher  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteSkirmisher; } 
  | UnitHandCannoneer  {}// static_cast<Condition*>(aiRule)->type = Unit::HandCannoneer; } 
  | UnitHeavyCavalryArcher  {}// static_cast<Condition*>(aiRule)->type = Unit::HeavyCavalryArcher; } 
  | UnitSkirmisher  {}// static_cast<Condition*>(aiRule)->type = Unit::Skirmisher; } 
  | UnitChampion  {}// static_cast<Condition*>(aiRule)->type = Unit::Champion; } 
  | UnitEagleWarrior  {}// static_cast<Condition*>(aiRule)->type = Unit::EagleWarrior; } 
  | UnitEliteEagleWarrior  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteEagleWarrior; } 
  | UnitHalberdier  {}// static_cast<Condition*>(aiRule)->type = Unit::Halberdier; } 
  | UnitLongSwordsman  {}// static_cast<Condition*>(aiRule)->type = Unit::LongSwordsman; } 
  | UnitManAtArms  {}// static_cast<Condition*>(aiRule)->type = Unit::ManAtArms; } 
  | UnitMilitiaman  {}// static_cast<Condition*>(aiRule)->type = Unit::Militiaman; } 
  | UnitPikeman  {}// static_cast<Condition*>(aiRule)->type = Unit::Pikeman; } 
  | UnitSpearman  {}// static_cast<Condition*>(aiRule)->type = Unit::Spearman; } 
  | UnitTwoHandedSwordsman  {}// static_cast<Condition*>(aiRule)->type = Unit::TwoHandedSwordsman; } 
  | UnitBerserk  {}// static_cast<Condition*>(aiRule)->type = Unit::Berserk; } 
  | UnitCataphract  {}// static_cast<Condition*>(aiRule)->type = Unit::Cataphract; } 
  | UnitChuKoNu  {}// static_cast<Condition*>(aiRule)->type = Unit::ChuKoNu; } 
  | UnitConquistador  {}// static_cast<Condition*>(aiRule)->type = Unit::Conquistador; } 
  | UnitEliteBerserk  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteBerserk; } 
  | UnitEliteCataphract  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteCataphract; } 
  | UnitEliteChuKoNu  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteChuKoNu; } 
  | UnitEliteConquistador  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteConquistador; } 
  | UnitEliteHuskarl  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteHuskarl; } 
  | UnitEliteJaguarWarrior  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteJaguarWarrior; } 
  | UnitEliteJanissary  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteJanissary; } 
  | UnitEliteLongbowman  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteLongbowman; } 
  | UnitEliteMameluke  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteMameluke; } 
  | UnitEliteMangudai  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteMangudai; } 
  | UnitElitePlumedArcher  {}// static_cast<Condition*>(aiRule)->type = Unit::ElitePlumedArcher; } 
  | UnitEliteSamurai  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteSamurai; } 
  | UnitEliteTarkan  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteTarkan; } 
  | UnitEliteTeutonicKnight  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteTeutonicKnight; } 
  | UnitEliteThrowingAxeman  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteThrowingAxeman; } 
  | UnitEliteWarElephant  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteWarElephant; } 
  | UnitEliteWarWagon  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteWarWagon; } 
  | UnitEliteWoadRaider  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteWoadRaider; } 
  | UnitHuskarl  {}// static_cast<Condition*>(aiRule)->type = Unit::Huskarl; } 
  | UnitJaguarWarrior  {}// static_cast<Condition*>(aiRule)->type = Unit::JaguarWarrior; } 
  | UnitJanissary  {}// static_cast<Condition*>(aiRule)->type = Unit::Janissary; } 
  | UnitLongbowman  {}// static_cast<Condition*>(aiRule)->type = Unit::Longbowman; } 
  | UnitMameluke  {}// static_cast<Condition*>(aiRule)->type = Unit::Mameluke; } 
  | UnitMangudai  {}// static_cast<Condition*>(aiRule)->type = Unit::Mangudai; } 
  | UnitPetard  {}// static_cast<Condition*>(aiRule)->type = Unit::Petard; } 
  | UnitPlumedArcher  {}// static_cast<Condition*>(aiRule)->type = Unit::PlumedArcher; } 
  | UnitSamurai  {}// static_cast<Condition*>(aiRule)->type = Unit::Samurai; } 
  | UnitTarkan  {}// static_cast<Condition*>(aiRule)->type = Unit::Tarkan; } 
  | UnitTeutonicKnight  {}// static_cast<Condition*>(aiRule)->type = Unit::TeutonicKnight; } 
  | UnitThrowingAxeman  {}// static_cast<Condition*>(aiRule)->type = Unit::ThrowingAxeman; } 
  | UnitTrebuchet  {}// static_cast<Condition*>(aiRule)->type = Unit::Trebuchet; } 
  | UnitWarElephant  {}// static_cast<Condition*>(aiRule)->type = Unit::WarElephant; } 
  | UnitWarWagon  {}// static_cast<Condition*>(aiRule)->type = Unit::WarWagon; } 
  | UnitWoadRaider  {}// static_cast<Condition*>(aiRule)->type = Unit::WoadRaider; } 
  | UnitCannonGalleon  {}// static_cast<Condition*>(aiRule)->type = Unit::CannonGalleon; } 
  | UnitDemolitionShip  {}// static_cast<Condition*>(aiRule)->type = Unit::DemolitionShip; } 
  | UnitEliteCannonGalleon  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteCannonGalleon; } 
  | UnitEliteLongboat  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteLongboat; } 
  | UnitEliteTurtleShip  {}// static_cast<Condition*>(aiRule)->type = Unit::EliteTurtleShip; } 
  | UnitFastFireShip  {}// static_cast<Condition*>(aiRule)->type = Unit::FastFireShip; } 
  | UnitFireShip  {}// static_cast<Condition*>(aiRule)->type = Unit::FireShip; } 
  | UnitFishingShip  {}// static_cast<Condition*>(aiRule)->type = Unit::FishingShip; } 
  | UnitGalleon  {}// static_cast<Condition*>(aiRule)->type = Unit::Galleon; } 
  | UnitGalley  {}// static_cast<Condition*>(aiRule)->type = Unit::Galley; } 
  | UnitHeavyDemolitionShip  {}// static_cast<Condition*>(aiRule)->type = Unit::HeavyDemolitionShip; } 
  | UnitLongboat  {}// static_cast<Condition*>(aiRule)->type = Unit::Longboat; } 
  | UnitTradeCog  {}// static_cast<Condition*>(aiRule)->type = Unit::TradeCog; } 
  | UnitTransportShip  {}// static_cast<Condition*>(aiRule)->type = Unit::TransportShip; } 
  | UnitTurtleShip  {}// static_cast<Condition*>(aiRule)->type = Unit::TurtleShip; } 
  | UnitWarGalley  {}// static_cast<Condition*>(aiRule)->type = Unit::WarGalley; } 
  | UnitTradeCart  {}// static_cast<Condition*>(aiRule)->type = Unit::TradeCart; } 
  | UnitMissionary  {}// static_cast<Condition*>(aiRule)->type = Unit::Missionary; } 
  | UnitMonk  {}// static_cast<Condition*>(aiRule)->type = Unit::Monk; } 
  | UnitBatteringRam  {}// static_cast<Condition*>(aiRule)->type = Unit::BatteringRam; } 
  | UnitBombardCannon  {}// static_cast<Condition*>(aiRule)->type = Unit::BombardCannon; } 
  | UnitCappedRam  {}// static_cast<Condition*>(aiRule)->type = Unit::CappedRam; } 
  | UnitHeavyScorpion  {}// static_cast<Condition*>(aiRule)->type = Unit::HeavyScorpion; } 
  | UnitMangonel  {}// static_cast<Condition*>(aiRule)->type = Unit::Mangonel; } 
  | UnitOnager  {}// static_cast<Condition*>(aiRule)->type = Unit::Onager; } 
  | UnitScorpion  {}// static_cast<Condition*>(aiRule)->type = Unit::Scorpion; } 
  | UnitSiegeOnager  {}// static_cast<Condition*>(aiRule)->type = Unit::SiegeOnager; } 
  | UnitSiegeRam  {}// static_cast<Condition*>(aiRule)->type = Unit::SiegeRam; } 
  | UnitCamel  {}// static_cast<Condition*>(aiRule)->type = Unit::Camel; } 
  | UnitCavalier  {}// static_cast<Condition*>(aiRule)->type = Unit::Cavalier; } 
  | UnitHeavyCamel  {}// static_cast<Condition*>(aiRule)->type = Unit::HeavyCamel; } 
  | UnitHussar  {}// static_cast<Condition*>(aiRule)->type = Unit::Hussar; } 
  | UnitKnight  {}// static_cast<Condition*>(aiRule)->type = Unit::Knight; } 
  | UnitLightCavalry  {}// static_cast<Condition*>(aiRule)->type = Unit::LightCavalry; } 
  | UnitPaladin  {}// static_cast<Condition*>(aiRule)->type = Unit::Paladin; } 
  | UnitScoutCavalry  {}// static_cast<Condition*>(aiRule)->type = Unit::ScoutCavalry; } 
  | UnitVillager  {}// static_cast<Condition*>(aiRule)->type = Unit::Villager; } 
  | UnitArcherLine  {}// static_cast<Condition*>(aiRule)->type = Unit::ArcherLine; } 
  | UnitCavalryArcherLine  {}// static_cast<Condition*>(aiRule)->type = Unit::CavalryArcherLine; } 
  | UnitSkirmisherLine  {}// static_cast<Condition*>(aiRule)->type = Unit::SkirmisherLine; } 
  | UnitEagleWarriorLine  {}// static_cast<Condition*>(aiRule)->type = Unit::EagleWarriorLine; } 
  | UnitMilitiamanLine  {}// static_cast<Condition*>(aiRule)->type = Unit::MilitiamanLine; } 
  | UnitSpearmanLine  {}// static_cast<Condition*>(aiRule)->type = Unit::SpearmanLine; } 
  | UnitBerserkLine  {}// static_cast<Condition*>(aiRule)->type = Unit::BerserkLine; } 
  | UnitCataphractLine  {}// static_cast<Condition*>(aiRule)->type = Unit::CataphractLine; } 
  | UnitChuKoNuLine  {}// static_cast<Condition*>(aiRule)->type = Unit::ChuKoNuLine; } 
  | UnitConquistadorLine  {}// static_cast<Condition*>(aiRule)->type = Unit::ConquistadorLine; } 
  | UnitHuskarlLine  {}// static_cast<Condition*>(aiRule)->type = Unit::HuskarlLine; } 
  | UnitJaguarWarriorLine  {}// static_cast<Condition*>(aiRule)->type = Unit::JaguarWarriorLine; } 
  | UnitJanissaryLine  {}// static_cast<Condition*>(aiRule)->type = Unit::JanissaryLine; } 
  | UnitLongbowmanLine  {}// static_cast<Condition*>(aiRule)->type = Unit::LongbowmanLine; } 
  | UnitMamelukeLine  {}// static_cast<Condition*>(aiRule)->type = Unit::MamelukeLine; } 
  | UnitMangudaiLine  {}// static_cast<Condition*>(aiRule)->type = Unit::MangudaiLine; } 
  | UnitPlumedArcherLine  {}// static_cast<Condition*>(aiRule)->type = Unit::PlumedArcherLine; } 
  | UnitSamuraiLine  {}// static_cast<Condition*>(aiRule)->type = Unit::SamuraiLine; } 
  | UnitTarkanLine  {}// static_cast<Condition*>(aiRule)->type = Unit::TarkanLine; } 
  | UnitTeutonicKnightLine  {}// static_cast<Condition*>(aiRule)->type = Unit::TeutonicKnightLine; } 
  | UnitThrowingAxemanLine  {}// static_cast<Condition*>(aiRule)->type = Unit::ThrowingAxemanLine; } 
  | UnitWarElephantLine  {}// static_cast<Condition*>(aiRule)->type = Unit::WarElephantLine; } 
  | UnitWarWagonLine  {}// static_cast<Condition*>(aiRule)->type = Unit::WarWagonLine; } 
  | UnitWoadRaiderLine  {}// static_cast<Condition*>(aiRule)->type = Unit::WoadRaiderLine; } 
  | UnitCannonGalleonLine  {}// static_cast<Condition*>(aiRule)->type = Unit::CannonGalleonLine; } 
  | UnitDemolitionShipLine  {}// static_cast<Condition*>(aiRule)->type = Unit::DemolitionShipLine; } 
  | UnitFireShipLine  {}// static_cast<Condition*>(aiRule)->type = Unit::FireShipLine; } 
  | UnitGalleyLine  {}// static_cast<Condition*>(aiRule)->type = Unit::GalleyLine; } 
  | UnitLongboatLine  {}// static_cast<Condition*>(aiRule)->type = Unit::LongboatLine; } 
  | UnitTurtleShipLine  {}// static_cast<Condition*>(aiRule)->type = Unit::TurtleShipLine; } 
  | UnitBatteringRamLine  {}// static_cast<Condition*>(aiRule)->type = Unit::BatteringRamLine; } 
  | UnitMangonelLine  {}// static_cast<Condition*>(aiRule)->type = Unit::MangonelLine; } 
  | UnitScorpionLine  {}// static_cast<Condition*>(aiRule)->type = Unit::ScorpionLine; } 
  | UnitCamelLine  {}// static_cast<Condition*>(aiRule)->type = Unit::CamelLine; } 
  | UnitKnightLine  {}// static_cast<Condition*>(aiRule)->type = Unit::KnightLine; } 
  | UnitScoutCavalryLine  {}// static_cast<Condition*>(aiRule)->type = Unit::ScoutCavalryLine; } 

value:
    Number
victorycondition:
    VictoryConditionStandard  {}// static_cast<Condition*>(aiRule)->type = VictoryCondition::Standard; } 
  | VictoryConditionConquest  {}// static_cast<Condition*>(aiRule)->type = VictoryCondition::Conquest; } 
  | VictoryConditionTimeLimit  {}// static_cast<Condition*>(aiRule)->type = VictoryCondition::TimeLimit; } 
  | VictoryConditionScore  {}// static_cast<Condition*>(aiRule)->type = VictoryCondition::Score; } 
  | VictoryConditionCustom  {}// static_cast<Condition*>(aiRule)->type = VictoryCondition::Custom; } 

walltype:
    WallTypeFortifiedWall  {}// static_cast<Condition*>(aiRule)->type = WallType::FortifiedWall; } 
  | WallTypePalisadeWall  {}// static_cast<Condition*>(aiRule)->type = WallType::PalisadeWall; } 
  | WallTypeStoneWall  {}// static_cast<Condition*>(aiRule)->type = WallType::StoneWall; } 
  | WallTypeStoneWallLine  {}// static_cast<Condition*>(aiRule)->type = WallType::StoneWallLine; } 


symbolname:
    age  | building  | civ  | commodity  | difficulty  | difficultyparameter  | diplomaticstance  | eventid  | eventtype  | goalid  | mapsize  | maptype  | perimeter  | playernumber  | relop  | researchitem  | sharedgoalid  | signalid  | startingresources  | strategicnumber  | stringid  | stringidrange  | stringidstart  | tauntid  | tauntrange  | tauntstart  | timerid  | unit  | value  | victorycondition  | walltype

donothing:
    DoNothing

acknowledgeevent:
    AcknowledgeEvent eventtype eventid

acknowledgetaunt:
    AcknowledgeTaunt playernumber tauntid

attacknow:
    AttackNow

build:
    Build building

buildforward:
    BuildForward building

buildgate:
    BuildGate perimeter

buildwall:
    BuildWall perimeter walltype

buycommodity:
    BuyCommodity commodity

ccaddresource:
    CcAddResource commodity value

chattoallusingid:
    ChatToAllUsingId stringid

chattoallusingrange:
    ChatToAllUsingRange stringidstart stringidrange

chattoalliesusingid:
    ChatToAlliesUsingId stringid

chattoalliesusingrange:
    ChatToAlliesUsingRange stringidstart stringidrange

chattoenemiesusingid:
    ChatToEnemiesUsingId stringid

chattoenemiesusingrange:
    ChatToEnemiesUsingRange stringidstart stringidrange

chattoplayerusingid:
    ChatToPlayerUsingId playernumber stringid

chattoplayerusingrange:
    ChatToPlayerUsingRange playernumber stringidstart stringidrange

chattrace:
    ChatTrace value

cleartributememory:
    ClearTributeMemory playernumber commodity

deletebuilding:
    DeleteBuilding building

deleteunit:
    DeleteUnit unit

disableself:
    DisableSelf

disabletimer:
    DisableTimer timerid

enabletimer:
    EnableTimer timerid

enablewallplacement:
    EnableWallPlacement perimeter

generaterandomnumber:
    GenerateRandomNumber value

logtrace:
    LogTrace value

releaseescrow:
    ReleaseEscrow commodity

research:
    Research researchitem

resign:
    Resign

sellcommodity:
    SellCommodity commodity

setdifficultyparameter:
    SetDifficultyParameter difficultyparameter value

setdoctrine:
    SetDoctrine value

setescrowpercentage:
    SetEscrowPercentage commodity value

setgoal:
    SetGoal goalid value

setsharedgoal:
    SetSharedGoal sharedgoalid value

setsignal:
    SetSignal signalid

setstance:
    SetStance playernumber diplomaticstance

setstrategicnumber:
    SetStrategicNumber strategicnumber value

spy:
    Spy

taunt:
    Taunt value

tauntusingrange:
    TauntUsingRange tauntstart tauntrange

train:
    Train unit

tributetoplayer:
    TributeToPlayer playernumber commodity value

action:
    donothing  | acknowledgeevent  | acknowledgetaunt  | attacknow  | build  | buildforward  | buildgate  | buildwall  | buycommodity  | ccaddresource  | chattoallusingid  | chattoallusingrange  | chattoalliesusingid  | chattoalliesusingrange  | chattoenemiesusingid  | chattoenemiesusingrange  | chattoplayerusingid  | chattoplayerusingrange  | chattrace  | cleartributememory  | deletebuilding  | deleteunit  | disableself  | disabletimer  | enabletimer  | enablewallplacement  | generaterandomnumber  | logtrace  | releaseescrow  | research  | research  | resign  | sellcommodity  | setdifficultyparameter  | setdoctrine  | setescrowpercentage  | setgoal  | setsharedgoal  | setsignal  | setstance  | setstrategicnumber  | spy  | taunt  | tauntusingrange  | train  | tributetoplayer

%%

int main() {
	yyin = stdin;

	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
