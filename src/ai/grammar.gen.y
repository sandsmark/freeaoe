%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

//%token LessThan LessOrEqual GreaterThan GreaterOrEqual Equal Not Or
%token Not Or

%token LoadIfDefined Else EndIf

%token Space NewLine

%start aiscript
%token AcknowledgeEvent
%token AcknowledgeTaunt
%token AgeDarkAge AgeFeudalAge AgeCastleAge AgeImperialAge AgePostImperialAge
%token AttackNow
%token AttackSoldierCount
%token AttackWarboatCount
%token Build
%token BuildForward
%token BuildGate
%token BuildingArcheryRange BuildingBarracks BuildingBlacksmith BuildingBombardTower BuildingCastle BuildingDock BuildingFarm BuildingFishTrap BuildingGuardTower BuildingHouse BuildingKeep BuildingLumberCamp BuildingMarket BuildingMill BuildingMiningCamp BuildingMonastery BuildingOutpost BuildingSiegeWorkshop BuildingStable BuildingTownCenter BuildingUniversity BuildingWatchTower BuildingWonder BuildingWatchTowerLine
%token BuildingAvailable
%token BuildingCount
%token BuildingCountTotal
%token BuildingTypeCount
%token BuildingTypeCountTotal
%token BuildWall
%token BuyCommodity
%token CanAffordBuilding
%token CanAffordCompleteWall
%token CanAffordResearch
%token CanAffordUnit
%token CanBuild
%token CanBuildGate
%token CanBuildGateWithEscrow
%token CanBuildWall
%token CanBuildWallWithEscrow
%token CanBuildWithEscrow
%token CanBuyCommodity
%token CanResearch
%token CanResearchWithEscrow
%token CanSellCommodity
%token CanSpy
%token CanSpyWithEscrow
%token CanTrain
%token CanTrainWithEscrow
%token CcAddResource
%token CcPlayersBuildingCount
%token CcPlayersBuildingTypeCount
%token CcPlayersUnitCount
%token CcPlayersUnitTypeCount
%token ChatLocal
%token ChatLocalToSelf
%token ChatLocalUsingId
%token ChatLocalUsingRange
%token ChatToAll
%token ChatToAllies
%token ChatToAlliesUsingId
%token ChatToAlliesUsingRange
%token ChatToAllUsingId
%token ChatToAllUsingRange
%token ChatToEnemies
%token ChatToEnemiesUsingId
%token ChatToEnemiesUsingRange
%token ChatToPlayer
%token ChatToPlayerUsingId
%token ChatToPlayerUsingRange
%token ChatTrace
%token CheatsEnabled
%token CivBriton CivByzantine CivCeltic CivChinese CivFrankish CivGothic CivJapanese CivMongol CivPersian CivSaracen CivTeutonic CivTurkish CivViking CivMyCiv
%token CivilianPopulation
%token CivSelected
%token ClearTributeMemory
%token CommodityBuyingPrice
%token CommodityFood CommodityStone CommodityWood CommodityGold
%token CommoditySellingPrice
%token CurrentAge
%token CurrentAgeTime
%token CurrentScore
%token DeathMatchGame
%token DefendSoldierCount
%token DefendWarboatCount
%token DeleteBuilding
%token DeleteUnit
%token Difficulty
%token DifficultyLevelEasiest DifficultyLevelEasy DifficultyLevelModerate DifficultyLevelHard DifficultyLevelHardest
%token DifficultyParameterAbilityToDodgeMissiles DifficultyParameterAbilityToMaintainDistance
%token DiplomaticStanceAlly DiplomaticStanceNeutral DiplomaticStanceEnemy
%token DisableSelf
%token DisableTimer
%token Doctrine
%token DoNothing
%token DropsiteMinDistance
%token EnableTimer
%token EnableWallPlacement
%token EnemyBuildingsInTown
%token EnemyCapturedRelics
%token EscrowAmount
%token EventDetected
%token False
%token FoodAmount
%token GameTime
%token GenerateRandomNumber
%token Goal
%token GoldAmount
%token HousingHeadroom
%token IdleFarmCount
%token Log
%token LogTrace
%token MapSize
%token MapSizeTypeTiny MapSizeTypeSmall MapSizeTypeMedium MapSizeTypeNormal MapSizeTypeLarge MapSizeTypeGiant
%token MapType
%token MapTypeNameArabia MapTypeNameArchipelago MapTypeNameBaltic MapTypeNameBlackForest MapTypeNameCoastal MapTypeNameContinental MapTypeNameCraterLake MapTypeNameFortress MapTypeNameGoldRush MapTypeNameHighland MapTypeNameIslands MapTypeNameMediterranean MapTypeNameMigration MapTypeNameRivers MapTypeNameTeamIslands MapTypeNameScenarioMap
%token MilitaryPopulation
%token PlayerComputer
%token PlayerHuman
%token PlayerInGame
%token PlayerNumber
%token PlayerNumberTypeAnyAlly PlayerNumberTypeAnyComputer PlayerNumberTypeAnyComputerAlly PlayerNumberTypeAnyComputerEnemy PlayerNumberTypeAnyComputerNeutral PlayerNumberTypeAnyEnemy PlayerNumberTypeAnyHuman PlayerNumberTypeAnyHumanAlly PlayerNumberTypeAnyHumanEnemy PlayerNumberTypeAnyHumanNeutral PlayerNumberTypeAnyNeutral PlayerNumberTypeEveryAlly PlayerNumberTypeEveryComputer PlayerNumberTypeEveryEnemy PlayerNumberTypeEveryHuman PlayerNumberTypeEveryNeutral PlayerNumberTypeMyPlayerNumber
%token PlayerResigned
%token PlayersBuildingCount
%token PlayersBuildingTypeCount
%token PlayersCiv
%token PlayersCivilianPopulation
%token PlayersCurrentAge
%token PlayersCurrentAgeTime
%token PlayersMilitaryPopulation
%token PlayersPopulation
%token PlayersScore
%token PlayersStance
%token PlayersTribute
%token PlayersTributeMemory
%token PlayersUnitCount
%token PlayersUnitTypeCount
%token PlayerValid
%token Population
%token PopulationCap
%token PopulationHeadroom
%token RandomNumber
%token RegicideGame
%token ReleaseEscrow
%token RelOpLessThan RelOpLessOrEqual RelOpGreaterThan RelOpGreaterOrEqual RelOpEqual RelOpNotEqual
%token Research
%token ResearchAvailable
%token ResearchCompleted
%token ResearchItemRiArbalest ResearchItemRiCrossbow ResearchItemRiEliteSkirmisher ResearchItemRiHandCannon ResearchItemRiHeavyCavalryArcher ResearchItemRiChampion ResearchItemRiEliteEagleWarrior ResearchItemRiHalberdier ResearchItemRiLongSwordsman ResearchItemRiManAtArms ResearchItemRiParthianTactics ResearchItemRiPikeman ResearchItemRiSquires ResearchItemRiThumbRing ResearchItemRiTracking ResearchItemRiTwoHandedSwordsman ResearchItemRiBlastFurnace ResearchItemRiBodkinArrow ResearchItemRiBracer ResearchItemRiChainBarding ResearchItemRiChainMail ResearchItemRiFletching ResearchItemRiForging ResearchItemRiIronCasting ResearchItemRiLeatherArcherArmor ResearchItemRiPaddedArcherArmor ResearchItemRiPlateBarding ResearchItemRiPlateMail ResearchItemRiRingArcherArmor ResearchItemRiScaleBarding ResearchItemRiScaleMail ResearchItemRiConscription ResearchItemRiHoardings ResearchItemRiSappers ResearchItemRiEliteBerserk ResearchItemRiEliteCataphract ResearchItemRiEliteChuKoNu ResearchItemRiEliteHuskarl ResearchItemRiEliteJanissary ResearchItemRiEliteLongbowman ResearchItemRiEliteMameluke ResearchItemRiEliteMangudai ResearchItemRiEliteSamurai ResearchItemRiEliteTeutonicKnight ResearchItemRiEliteThrowingAxeman ResearchItemRiEliteWarElephant ResearchItemRiEliteWoadRaider ResearchItemRiMyUniqueEliteUnit ResearchItemRiMyUniqueResearch ResearchItemRiCannonGalleon ResearchItemRiCareening ResearchItemRiDeckGuns ResearchItemRiDryDock ResearchItemRiEliteLongboat ResearchItemRiFastFireShip ResearchItemRiGalleon ResearchItemRiHeavyDemolitionShip ResearchItemRiShipwright ResearchItemRiWarGalley ResearchItemRiBowSaw ResearchItemRiDoubleBitAxe ResearchItemRiTwoManSaw ResearchItemRiBanking ResearchItemRiCaravan ResearchItemRiCartography ResearchItemRiCoinage ResearchItemRiGuilds ResearchItemRiCropRotation ResearchItemRiHeavyPlow ResearchItemRiHorseCollar ResearchItemRiGoldMining ResearchItemRiGoldShaftMining ResearchItemRiStoneMining ResearchItemRiStoneShaftMining ResearchItemRiAtonement ResearchItemRiBlockPrinting ResearchItemRiFaith ResearchItemRiFervor ResearchItemRiHerbalMedicine ResearchItemRiHeresy ResearchItemRiIllumination ResearchItemRiRedemption ResearchItemRiSanctity ResearchItemRiTheocracy ResearchItemRiBombardCannon ResearchItemRiCappedRam ResearchItemRiHeavyScorpion ResearchItemRiOnager ResearchItemRiScorpion ResearchItemRiSiegeOnager ResearchItemRiSiegeRam ResearchItemRiBloodlines ResearchItemRiCavalier ResearchItemRiHeavyCamel ResearchItemRiHusbandry ResearchItemRiHussar ResearchItemRiLightCavalry ResearchItemRiPaladin ResearchItemRiHandCart ResearchItemRiLoom ResearchItemRiTownPatrol ResearchItemRiTownWatch ResearchItemRiWheelBarrow ResearchItemRiArchitecture ResearchItemRiBallistics ResearchItemRiBombardTower ResearchItemRiChemistry ResearchItemRiFortifiedWall ResearchItemRiGuardTower ResearchItemRiHeatedShot ResearchItemRiKeep ResearchItemRiMasonry ResearchItemRiMurderHoles ResearchItemRiSiegeEngineers ResearchItemRiStonecutting ResearchItemMyUniqueUnitUpgrade ResearchItemMyUniqueResearch
%token Resign
%token ResourceFound
%token SellCommodity
%token SetDifficultyParameter
%token SetDoctrine
%token SetEscrowPercentage
%token SetGoal
%token SetSharedGoal
%token SetSignal
%token SetStance
%token SetStrategicNumber
%token SharedGoal
%token SheepAndForageTooFar
%token SoldierCount
%token Spy
%token StanceToward
%token StartingAge
%token StartingResources
%token StartingResourcesTypeLowResources StartingResourcesTypeMediumResources StartingResourcesTypeHighResources
%token StoneAmount
%token StrategicNumber
%token StrategicNumberNameSnPercentCivilianExplorers StrategicNumberNameSnPercentCivilianBuilders StrategicNumberNameSnPercentCivilianGatherers StrategicNumberNameSnCapCivilianExplorers StrategicNumberNameSnCapCivilianBuilders StrategicNumberNameSnCapCivilianGatherers StrategicNumberNameSnMinimumAttackGroupSize StrategicNumberNameSnTotalNumberExplorers StrategicNumberNameSnPercentEnemySightedResponse StrategicNumberNameSnEnemySightedResponseDistance StrategicNumberNameSnSentryDistance StrategicNumberNameSnRelicReturnDistance StrategicNumberNameSnMinimumDefendGroupSize StrategicNumberNameSnMaximumAttackGroupSize StrategicNumberNameSnMaximumDefendGroupSize StrategicNumberNameSnMinimumPeaceLikeLevel StrategicNumberNameSnPercentExplorationRequired StrategicNumberNameSnZeroPriorityDistance StrategicNumberNameSnMinimumCivilianExplorers StrategicNumberNameSnNumberAttackGroups StrategicNumberNameSnNumberDefendGroups StrategicNumberNameSnAttackGroupGatherSpacing StrategicNumberNameSnNumberExploreGroups StrategicNumberNameSnMinimumExploreGroupSize StrategicNumberNameSnMaximumExploreGroupSize StrategicNumberNameSnGoldDefendPriority StrategicNumberNameSnStoneDefendPriority StrategicNumberNameSnForageDefendPriority StrategicNumberNameSnRelicDefendPriority StrategicNumberNameSnTownDefendPriority StrategicNumberNameSnDefenseDistance StrategicNumberNameSnNumberBoatAttackGroups StrategicNumberNameSnMinimumBoatAttackGroupSize StrategicNumberNameSnMaximumBoatAttackGroupSize StrategicNumberNameSnNumberBoatExploreGroups StrategicNumberNameSnMinimumBoatExploreGroupSize StrategicNumberNameSnMaximumBoatExploreGroupSize StrategicNumberNameSnNumberBoatDefendGroups StrategicNumberNameSnMinimumBoatDefendGroupSize StrategicNumberNameSnMaximumBoatDefendGroupSize StrategicNumberNameSnDockDefendPriority StrategicNumberNameSnSentryDistanceVariation StrategicNumberNameSnMinimumTownSize StrategicNumberNameSnMaximumTownSize StrategicNumberNameSnGroupCommanderSelectionMethod StrategicNumberNameSnConsecutiveIdleUnitLimit StrategicNumberNameSnTargetEvaluationDistance StrategicNumberNameSnTargetEvaluationHitpoints StrategicNumberNameSnTargetEvaluationDamageCapability StrategicNumberNameSnTargetEvaluationKills StrategicNumberNameSnTargetEvaluationAllyProximity StrategicNumberNameSnTargetEvaluationRof StrategicNumberNameSnTargetEvaluationRandomness StrategicNumberNameSnCampMaxDistance StrategicNumberNameSnMillMaxDistance StrategicNumberNameSnTargetEvaluationAttackAttempts StrategicNumberNameSnTargetEvaluationRange StrategicNumberNameSnDefendOverlapDistance StrategicNumberNameSnScaleMinimumAttackGroupSize StrategicNumberNameSnScaleMaximumAttackGroupSize StrategicNumberNameSnAttackGroupSizeRandomness StrategicNumberNameSnScalingFrequency StrategicNumberNameSnMaximumGaiaAttackResponse StrategicNumberNameSnBuildFrequency StrategicNumberNameSnAttackSeparationTimeRandomness StrategicNumberNameSnAttackIntelligence StrategicNumberNameSnInitialAttackDelay StrategicNumberNameSnSaveScenarioInformation StrategicNumberNameSnSpecialAttackType1 StrategicNumberNameSnSpecialAttackInfluence1 StrategicNumberNameSnMinimumWaterBodySizeForDock StrategicNumberNameSnNumberBuildAttemptsBeforeSkip StrategicNumberNameSnMaxSkipsPerAttempt StrategicNumberNameSnFoodGathererPercentage StrategicNumberNameSnGoldGathererPercentage StrategicNumberNameSnStoneGathererPercentage StrategicNumberNameSnWoodGathererPercentage StrategicNumberNameSnTargetEvaluationContinent StrategicNumberNameSnTargetEvaluationSiegeWeapon StrategicNumberNameSnGroupLeaderDefenseDistance StrategicNumberNameSnInitialAttackDelayType StrategicNumberNameSnBlotExplorationMap StrategicNumberNameSnBlotSize StrategicNumberNameSnIntelligentGathering StrategicNumberNameSnTaskUngroupedSoldiers StrategicNumberNameSnTargetEvaluationBoat StrategicNumberNameSnNumberEnemyObjectsRequired StrategicNumberNameSnNumberMaxSkipCycles StrategicNumberNameSnRetaskGatherAmount StrategicNumberNameSnMaxRetaskGatherAmount StrategicNumberNameSnMaxBuildPlanGathererPercentage StrategicNumberNameSnFoodDropsiteDistance StrategicNumberNameSnWoodDropsiteDistance StrategicNumberNameSnStoneDropsiteDistance StrategicNumberNameSnGoldDropsiteDistance StrategicNumberNameSnInitialExplorationRequired StrategicNumberNameSnRandomPlacementFactor StrategicNumberNameSnRequiredForestTiles StrategicNumberNameSnAttackDiplomacyImpact StrategicNumberNameSnPercentHalfExploration StrategicNumberNameSnTargetEvaluationTimeKillRatio StrategicNumberNameSnTargetEvaluationInProgress StrategicNumberNameSnAttackWinningPlayer StrategicNumberNameSnCoopShareInformation StrategicNumberNameSnAttackWinningPlayerFactor StrategicNumberNameSnCoopShareAttacking StrategicNumberNameSnCoopShareAttackingInterval StrategicNumberNameSnPercentageExploreExterminators StrategicNumberNameSnTrackPlayerHistory StrategicNumberNameSnMinimumDropsiteBuffer StrategicNumberNameSnUseByTypeMaxGathering StrategicNumberNameSnMinimumBoarHuntGroupSize StrategicNumberNameSnMinimumAmountForTrading StrategicNumberNameSnEasiestReactionPercentage StrategicNumberNameSnEasierReactionPercentage StrategicNumberNameSnHitsBeforeAllianceChange StrategicNumberNameSnAllowCivilianDefense StrategicNumberNameSnNumberForwardBuilders StrategicNumberNameSnPercentAttackSoldiers StrategicNumberNameSnPercentAttackBoats StrategicNumberNameSnDoNotScaleForDifficultyLevel StrategicNumberNameSnGroupFormDistance StrategicNumberNameSnIgnoreAttackGroupUnderAttack StrategicNumberNameSnGatherDefenseUnits StrategicNumberNameSnMaximumWoodDropDistance StrategicNumberNameSnMaximumFoodDropDistance StrategicNumberNameSnMaximumHuntDropDistance StrategicNumberNameSnMaximumFishBoatDropDistance StrategicNumberNameSnMaximumGoldDropDistance StrategicNumberNameSnMaximumStoneDropDistance StrategicNumberNameSnGatherIdleSoldiersAtCenter StrategicNumberNameSnGarrisonRams
%token Taunt
%token TauntDetected
%token TauntUsingRange
%token TimerTriggered
%token TownUnderAttack
%token Train
%token TributeToPlayer
%token True
%token UnitArbalest UnitArcher UnitCavalryArcher UnitCrossbowman UnitEliteSkirmisher UnitHandCannoneer UnitHeavyCavalryArcher UnitSkirmisher UnitChampion UnitEagleWarrior UnitEliteEagleWarrior UnitHalberdier UnitLongSwordsman UnitManAtArms UnitMilitiaman UnitPikeman UnitSpearman UnitTwoHandedSwordsman UnitBerserk UnitCataphract UnitChuKoNu UnitConquistador UnitEliteBerserk UnitEliteCataphract UnitEliteChuKoNu UnitEliteConquistador UnitEliteHuskarl UnitEliteJaguarWarrior UnitEliteJanissary UnitEliteLongbowman UnitEliteMameluke UnitEliteMangudai UnitElitePlumedArcher UnitEliteSamurai UnitEliteTarkan UnitEliteTeutonicKnight UnitEliteThrowingAxeman UnitEliteWarElephant UnitEliteWarWagon UnitEliteWoadRaider UnitHuskarl UnitJaguarWarrior UnitJanissary UnitLongbowman UnitMameluke UnitMangudai UnitPetard UnitPlumedArcher UnitSamurai UnitTarkan UnitTeutonicKnight UnitThrowingAxeman UnitTrebuchet UnitWarElephant UnitWarWagon UnitWoadRaider UnitCannonGalleon UnitDemolitionShip UnitEliteCannonGalleon UnitEliteLongboat UnitEliteTurtleShip UnitFastFireShip UnitFireShip UnitFishingShip UnitGalleon UnitGalley UnitHeavyDemolitionShip UnitLongboat UnitTradeCog UnitTransportShip UnitTurtleShip UnitWarGalley UnitTradeCart UnitMissionary UnitMonk UnitBatteringRam UnitBombardCannon UnitCappedRam UnitHeavyScorpion UnitMangonel UnitOnager UnitScorpion UnitSiegeOnager UnitSiegeRam UnitCamel UnitCavalier UnitHeavyCamel UnitHussar UnitKnight UnitLightCavalry UnitPaladin UnitScoutCavalry UnitVillager UnitArcherLine UnitCavalryArcherLine UnitSkirmisherLine UnitEagleWarriorLine UnitMilitiamanLine UnitSpearmanLine UnitBerserkLine UnitCataphractLine UnitChuKoNuLine UnitConquistadorLine UnitHuskarlLine UnitJaguarWarriorLine UnitJanissaryLine UnitLongbowmanLine UnitMamelukeLine UnitMangudaiLine UnitPlumedArcherLine UnitSamuraiLine UnitTarkanLine UnitTeutonicKnightLine UnitThrowingAxemanLine UnitWarElephantLine UnitWarWagonLine UnitWoadRaiderLine UnitCannonGalleonLine UnitDemolitionShipLine UnitFireShipLine UnitGalleyLine UnitLongboatLine UnitTurtleShipLine UnitBatteringRamLine UnitMangonelLine UnitScorpionLine UnitCamelLine UnitKnightLine UnitScoutCavalryLine UnitMyEliteUniqueUnit UnitMyUniqueUnit UnitMyUniqueUnitLine
%token UnitAvailable
%token UnitCount
%token UnitCountTotal
%token UnitTypeCount
%token UnitTypeCountTotal
%token VictoryCondition
%token VictoryConditionNameStandard VictoryConditionNameConquest VictoryConditionNameTimeLimit VictoryConditionNameScore VictoryConditionNameCustom
%token WallCompletedPercentage
%token WallInvisiblePercentage
%token WallTypeFortifiedWall WallTypePalisadeWall WallTypeStoneWall WallTypeStoneWallLine
%token WarboatCount
%token WoodAmount
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
    OpenParen conditiontype CloseParen { printf("condition\n"); }

conditiontype:
    Not condition { printf("got negated condition\n"); }
    | Or conditions { printf("got multiple or conditions\n"); }
    | fact { printf("got fact\n"); }


//condition:
//    OpenParen Not condition CloseParen {}//  printf("got negated condition\n"); }
//    | OpenParen Or conditions CloseParen { }// printf("got multiple or conditions\n"); }
//    | OpenParen symbolname CloseParen {}//  printf("got condition with symbol '%s'\n", $2); }
//    | OpenParen symbolname Number CloseParen {}//  printf("got condition with symbol '%s' and number %d\n", $2, $3); }
//    | OpenParen symbolname Number Number CloseParen {}//  printf("got condition with symbol '%s' and numbers %d %d\n", $2, $3, $4); }
//    | OpenParen symbolname symbolname CloseParen {}//  printf("got condition with two symbols '%s' %s\n", $2, $3); }
//    | OpenParen symbolname symbolname symbolname CloseParen {}//  printf("got condition with three symbols %s %s %s\n", $2, $3, $4); }
//    | OpenParen symbolname relop Number CloseParen {}//  printf("got condition with comparison %s %d\n", $2, $4); }
//    | OpenParen symbolname relop symbolname CloseParen {}//  printf("got condition with comparison %s %s\n", $2, $4); }
//    | OpenParen symbolname symbolname relop symbolname CloseParen {}//  printf("got condition with comparison %s %s %s\n", $2, $3, $5); }
//    | OpenParen symbolname symbolname relop Number CloseParen {}//  printf("got condition with comparison %s %s %d\n", $2, $3, $5); }
//    | OpenParen symbolname symbolname symbolname relop Number CloseParen {}//  printf("got condition with comparison %s %s %s %d\n", $2, $3, $4, $6); }
//
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


//comparison:
//    RelOpLessThan {  printf("got lessthan\n"); }
//    | RelOpLessOrEqual {  printf("got lessorequal\n"); }
//    | RelOpGreaterThan {  printf("got greaterthan\n"); }
//    | RelOpGreaterOrEqual {  printf("got greaterorequal\n"); }
//    | RelOpEqual {  printf("got equals\n"); }

//actions:
//    OpenParen singleaction CloseParen {  printf("got single action\n"); }
//    | singleaction actions {  printf("got multiple actions\n"); }

actions:
    singleaction {  printf("got single action\n"); }
    | singleaction actions {  printf("got multiple actions\n"); }

singleaction:
      OpenParen action CloseParen { printf("got action without arguments\n"); }

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
| BuildingCastle 

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
  | CivMyCiv  {}// static_cast<Condition*>(aiRule)->type = Civ::MyCiv; } 

commodity:
    CommodityFood  {}// static_cast<Condition*>(aiRule)->type = Commodity::Food; } 
  | CommodityStone  {}// static_cast<Condition*>(aiRule)->type = Commodity::Stone; } 
  | CommodityWood  {}// static_cast<Condition*>(aiRule)->type = Commodity::Wood; } 
  | CommodityGold  {}// static_cast<Condition*>(aiRule)->type = Commodity::Gold; } 

difficultylevel:
    DifficultyLevelEasiest  {}// static_cast<Condition*>(aiRule)->type = DifficultyLevel::Easiest; } 
  | DifficultyLevelEasy  {}// static_cast<Condition*>(aiRule)->type = DifficultyLevel::Easy; } 
  | DifficultyLevelModerate  {}// static_cast<Condition*>(aiRule)->type = DifficultyLevel::Moderate; } 
  | DifficultyLevelHard  {}// static_cast<Condition*>(aiRule)->type = DifficultyLevel::Hard; } 
  | DifficultyLevelHardest  {}// static_cast<Condition*>(aiRule)->type = DifficultyLevel::Hardest; } 

difficultyparameter:
    DifficultyParameterAbilityToDodgeMissiles  {}// static_cast<Condition*>(aiRule)->type = DifficultyParameter::AbilityToDodgeMissiles; } 
  | DifficultyParameterAbilityToMaintainDistance  {}// static_cast<Condition*>(aiRule)->type = DifficultyParameter::AbilityToMaintainDistance; } 

diplomaticstance:
    DiplomaticStanceAlly  {}// static_cast<Condition*>(aiRule)->type = DiplomaticStance::Ally; } 
  | DiplomaticStanceNeutral  {}// static_cast<Condition*>(aiRule)->type = DiplomaticStance::Neutral; } 
  | DiplomaticStanceEnemy  {}// static_cast<Condition*>(aiRule)->type = DiplomaticStance::Enemy; } 

mapsizetype:
    MapSizeTypeTiny  {}// static_cast<Condition*>(aiRule)->type = MapSizeType::Tiny; } 
  | MapSizeTypeSmall  {}// static_cast<Condition*>(aiRule)->type = MapSizeType::Small; } 
  | MapSizeTypeMedium  {}// static_cast<Condition*>(aiRule)->type = MapSizeType::Medium; } 
  | MapSizeTypeNormal  {}// static_cast<Condition*>(aiRule)->type = MapSizeType::Normal; } 
  | MapSizeTypeLarge  {}// static_cast<Condition*>(aiRule)->type = MapSizeType::Large; } 
  | MapSizeTypeGiant  {}// static_cast<Condition*>(aiRule)->type = MapSizeType::Giant; } 

maptypename:
    MapTypeNameArabia  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Arabia; } 
  | MapTypeNameArchipelago  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Archipelago; } 
  | MapTypeNameBaltic  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Baltic; } 
  | MapTypeNameBlackForest  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::BlackForest; } 
  | MapTypeNameCoastal  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Coastal; } 
  | MapTypeNameContinental  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Continental; } 
  | MapTypeNameCraterLake  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::CraterLake; } 
  | MapTypeNameFortress  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Fortress; } 
  | MapTypeNameGoldRush  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::GoldRush; } 
  | MapTypeNameHighland  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Highland; } 
  | MapTypeNameIslands  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Islands; } 
  | MapTypeNameMediterranean  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Mediterranean; } 
  | MapTypeNameMigration  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Migration; } 
  | MapTypeNameRivers  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::Rivers; } 
  | MapTypeNameTeamIslands  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::TeamIslands; } 
  | MapTypeNameScenarioMap  {}// static_cast<Condition*>(aiRule)->type = MapTypeName::ScenarioMap; } 

playernumbertype:
    PlayerNumberTypeAnyAlly  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyAlly; } 
  | PlayerNumberTypeAnyComputer  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyComputer; } 
  | PlayerNumberTypeAnyComputerAlly  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyComputerAlly; } 
  | PlayerNumberTypeAnyComputerEnemy  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyComputerEnemy; } 
  | PlayerNumberTypeAnyComputerNeutral  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyComputerNeutral; } 
  | PlayerNumberTypeAnyEnemy  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyEnemy; } 
  | PlayerNumberTypeAnyHuman  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyHuman; } 
  | PlayerNumberTypeAnyHumanAlly  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyHumanAlly; } 
  | PlayerNumberTypeAnyHumanEnemy  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyHumanEnemy; } 
  | PlayerNumberTypeAnyHumanNeutral  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyHumanNeutral; } 
  | PlayerNumberTypeAnyNeutral  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::AnyNeutral; } 
  | PlayerNumberTypeEveryAlly  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::EveryAlly; } 
  | PlayerNumberTypeEveryComputer  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::EveryComputer; } 
  | PlayerNumberTypeEveryEnemy  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::EveryEnemy; } 
  | PlayerNumberTypeEveryHuman  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::EveryHuman; } 
  | PlayerNumberTypeEveryNeutral  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::EveryNeutral; } 
  | PlayerNumberTypeMyPlayerNumber  {}// static_cast<Condition*>(aiRule)->type = PlayerNumberType::MyPlayerNumber; } 

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
  | ResearchItemMyUniqueUnitUpgrade  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::MyUniqueUnitUpgrade; } 
  | ResearchItemMyUniqueResearch  {}// static_cast<Condition*>(aiRule)->type = ResearchItem::MyUniqueResearch; } 

startingresourcestype:
    StartingResourcesTypeLowResources  {}// static_cast<Condition*>(aiRule)->type = StartingResourcesType::LowResources; } 
  | StartingResourcesTypeMediumResources  {}// static_cast<Condition*>(aiRule)->type = StartingResourcesType::MediumResources; } 
  | StartingResourcesTypeHighResources  {}// static_cast<Condition*>(aiRule)->type = StartingResourcesType::HighResources; } 

strategicnumbername:
    StrategicNumberNameSnPercentCivilianExplorers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnPercentCivilianExplorers; } 
  | StrategicNumberNameSnPercentCivilianBuilders  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnPercentCivilianBuilders; } 
  | StrategicNumberNameSnPercentCivilianGatherers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnPercentCivilianGatherers; } 
  | StrategicNumberNameSnCapCivilianExplorers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnCapCivilianExplorers; } 
  | StrategicNumberNameSnCapCivilianBuilders  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnCapCivilianBuilders; } 
  | StrategicNumberNameSnCapCivilianGatherers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnCapCivilianGatherers; } 
  | StrategicNumberNameSnMinimumAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumAttackGroupSize; } 
  | StrategicNumberNameSnTotalNumberExplorers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTotalNumberExplorers; } 
  | StrategicNumberNameSnPercentEnemySightedResponse  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnPercentEnemySightedResponse; } 
  | StrategicNumberNameSnEnemySightedResponseDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnEnemySightedResponseDistance; } 
  | StrategicNumberNameSnSentryDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnSentryDistance; } 
  | StrategicNumberNameSnRelicReturnDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnRelicReturnDistance; } 
  | StrategicNumberNameSnMinimumDefendGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumDefendGroupSize; } 
  | StrategicNumberNameSnMaximumAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumAttackGroupSize; } 
  | StrategicNumberNameSnMaximumDefendGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumDefendGroupSize; } 
  | StrategicNumberNameSnMinimumPeaceLikeLevel  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumPeaceLikeLevel; } 
  | StrategicNumberNameSnPercentExplorationRequired  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnPercentExplorationRequired; } 
  | StrategicNumberNameSnZeroPriorityDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnZeroPriorityDistance; } 
  | StrategicNumberNameSnMinimumCivilianExplorers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumCivilianExplorers; } 
  | StrategicNumberNameSnNumberAttackGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnNumberAttackGroups; } 
  | StrategicNumberNameSnNumberDefendGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnNumberDefendGroups; } 
  | StrategicNumberNameSnAttackGroupGatherSpacing  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnAttackGroupGatherSpacing; } 
  | StrategicNumberNameSnNumberExploreGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnNumberExploreGroups; } 
  | StrategicNumberNameSnMinimumExploreGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumExploreGroupSize; } 
  | StrategicNumberNameSnMaximumExploreGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumExploreGroupSize; } 
  | StrategicNumberNameSnGoldDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnGoldDefendPriority; } 
  | StrategicNumberNameSnStoneDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnStoneDefendPriority; } 
  | StrategicNumberNameSnForageDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnForageDefendPriority; } 
  | StrategicNumberNameSnRelicDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnRelicDefendPriority; } 
  | StrategicNumberNameSnTownDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTownDefendPriority; } 
  | StrategicNumberNameSnDefenseDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnDefenseDistance; } 
  | StrategicNumberNameSnNumberBoatAttackGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnNumberBoatAttackGroups; } 
  | StrategicNumberNameSnMinimumBoatAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumBoatAttackGroupSize; } 
  | StrategicNumberNameSnMaximumBoatAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumBoatAttackGroupSize; } 
  | StrategicNumberNameSnNumberBoatExploreGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnNumberBoatExploreGroups; } 
  | StrategicNumberNameSnMinimumBoatExploreGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumBoatExploreGroupSize; } 
  | StrategicNumberNameSnMaximumBoatExploreGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumBoatExploreGroupSize; } 
  | StrategicNumberNameSnNumberBoatDefendGroups  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnNumberBoatDefendGroups; } 
  | StrategicNumberNameSnMinimumBoatDefendGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumBoatDefendGroupSize; } 
  | StrategicNumberNameSnMaximumBoatDefendGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumBoatDefendGroupSize; } 
  | StrategicNumberNameSnDockDefendPriority  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnDockDefendPriority; } 
  | StrategicNumberNameSnSentryDistanceVariation  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnSentryDistanceVariation; } 
  | StrategicNumberNameSnMinimumTownSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumTownSize; } 
  | StrategicNumberNameSnMaximumTownSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumTownSize; } 
  | StrategicNumberNameSnGroupCommanderSelectionMethod  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnGroupCommanderSelectionMethod; } 
  | StrategicNumberNameSnConsecutiveIdleUnitLimit  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnConsecutiveIdleUnitLimit; } 
  | StrategicNumberNameSnTargetEvaluationDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationDistance; } 
  | StrategicNumberNameSnTargetEvaluationHitpoints  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationHitpoints; } 
  | StrategicNumberNameSnTargetEvaluationDamageCapability  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationDamageCapability; } 
  | StrategicNumberNameSnTargetEvaluationKills  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationKills; } 
  | StrategicNumberNameSnTargetEvaluationAllyProximity  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationAllyProximity; } 
  | StrategicNumberNameSnTargetEvaluationRof  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationRof; } 
  | StrategicNumberNameSnTargetEvaluationRandomness  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationRandomness; } 
  | StrategicNumberNameSnCampMaxDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnCampMaxDistance; } 
  | StrategicNumberNameSnMillMaxDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMillMaxDistance; } 
  | StrategicNumberNameSnTargetEvaluationAttackAttempts  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationAttackAttempts; } 
  | StrategicNumberNameSnTargetEvaluationRange  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationRange; } 
  | StrategicNumberNameSnDefendOverlapDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnDefendOverlapDistance; } 
  | StrategicNumberNameSnScaleMinimumAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnScaleMinimumAttackGroupSize; } 
  | StrategicNumberNameSnScaleMaximumAttackGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnScaleMaximumAttackGroupSize; } 
  | StrategicNumberNameSnAttackGroupSizeRandomness  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnAttackGroupSizeRandomness; } 
  | StrategicNumberNameSnScalingFrequency  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnScalingFrequency; } 
  | StrategicNumberNameSnMaximumGaiaAttackResponse  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumGaiaAttackResponse; } 
  | StrategicNumberNameSnBuildFrequency  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnBuildFrequency; } 
  | StrategicNumberNameSnAttackSeparationTimeRandomness  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnAttackSeparationTimeRandomness; } 
  | StrategicNumberNameSnAttackIntelligence  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnAttackIntelligence; } 
  | StrategicNumberNameSnInitialAttackDelay  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnInitialAttackDelay; } 
  | StrategicNumberNameSnSaveScenarioInformation  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnSaveScenarioInformation; } 
  | StrategicNumberNameSnSpecialAttackType1  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnSpecialAttackType1; } 
  | StrategicNumberNameSnSpecialAttackInfluence1  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnSpecialAttackInfluence1; } 
  | StrategicNumberNameSnMinimumWaterBodySizeForDock  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumWaterBodySizeForDock; } 
  | StrategicNumberNameSnNumberBuildAttemptsBeforeSkip  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnNumberBuildAttemptsBeforeSkip; } 
  | StrategicNumberNameSnMaxSkipsPerAttempt  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaxSkipsPerAttempt; } 
  | StrategicNumberNameSnFoodGathererPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnFoodGathererPercentage; } 
  | StrategicNumberNameSnGoldGathererPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnGoldGathererPercentage; } 
  | StrategicNumberNameSnStoneGathererPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnStoneGathererPercentage; } 
  | StrategicNumberNameSnWoodGathererPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnWoodGathererPercentage; } 
  | StrategicNumberNameSnTargetEvaluationContinent  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationContinent; } 
  | StrategicNumberNameSnTargetEvaluationSiegeWeapon  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationSiegeWeapon; } 
  | StrategicNumberNameSnGroupLeaderDefenseDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnGroupLeaderDefenseDistance; } 
  | StrategicNumberNameSnInitialAttackDelayType  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnInitialAttackDelayType; } 
  | StrategicNumberNameSnBlotExplorationMap  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnBlotExplorationMap; } 
  | StrategicNumberNameSnBlotSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnBlotSize; } 
  | StrategicNumberNameSnIntelligentGathering  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnIntelligentGathering; } 
  | StrategicNumberNameSnTaskUngroupedSoldiers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTaskUngroupedSoldiers; } 
  | StrategicNumberNameSnTargetEvaluationBoat  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationBoat; } 
  | StrategicNumberNameSnNumberEnemyObjectsRequired  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnNumberEnemyObjectsRequired; } 
  | StrategicNumberNameSnNumberMaxSkipCycles  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnNumberMaxSkipCycles; } 
  | StrategicNumberNameSnRetaskGatherAmount  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnRetaskGatherAmount; } 
  | StrategicNumberNameSnMaxRetaskGatherAmount  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaxRetaskGatherAmount; } 
  | StrategicNumberNameSnMaxBuildPlanGathererPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaxBuildPlanGathererPercentage; } 
  | StrategicNumberNameSnFoodDropsiteDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnFoodDropsiteDistance; } 
  | StrategicNumberNameSnWoodDropsiteDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnWoodDropsiteDistance; } 
  | StrategicNumberNameSnStoneDropsiteDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnStoneDropsiteDistance; } 
  | StrategicNumberNameSnGoldDropsiteDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnGoldDropsiteDistance; } 
  | StrategicNumberNameSnInitialExplorationRequired  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnInitialExplorationRequired; } 
  | StrategicNumberNameSnRandomPlacementFactor  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnRandomPlacementFactor; } 
  | StrategicNumberNameSnRequiredForestTiles  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnRequiredForestTiles; } 
  | StrategicNumberNameSnAttackDiplomacyImpact  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnAttackDiplomacyImpact; } 
  | StrategicNumberNameSnPercentHalfExploration  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnPercentHalfExploration; } 
  | StrategicNumberNameSnTargetEvaluationTimeKillRatio  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationTimeKillRatio; } 
  | StrategicNumberNameSnTargetEvaluationInProgress  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTargetEvaluationInProgress; } 
  | StrategicNumberNameSnAttackWinningPlayer  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnAttackWinningPlayer; } 
  | StrategicNumberNameSnCoopShareInformation  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnCoopShareInformation; } 
  | StrategicNumberNameSnAttackWinningPlayerFactor  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnAttackWinningPlayerFactor; } 
  | StrategicNumberNameSnCoopShareAttacking  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnCoopShareAttacking; } 
  | StrategicNumberNameSnCoopShareAttackingInterval  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnCoopShareAttackingInterval; } 
  | StrategicNumberNameSnPercentageExploreExterminators  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnPercentageExploreExterminators; } 
  | StrategicNumberNameSnTrackPlayerHistory  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnTrackPlayerHistory; } 
  | StrategicNumberNameSnMinimumDropsiteBuffer  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumDropsiteBuffer; } 
  | StrategicNumberNameSnUseByTypeMaxGathering  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnUseByTypeMaxGathering; } 
  | StrategicNumberNameSnMinimumBoarHuntGroupSize  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumBoarHuntGroupSize; } 
  | StrategicNumberNameSnMinimumAmountForTrading  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMinimumAmountForTrading; } 
  | StrategicNumberNameSnEasiestReactionPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnEasiestReactionPercentage; } 
  | StrategicNumberNameSnEasierReactionPercentage  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnEasierReactionPercentage; } 
  | StrategicNumberNameSnHitsBeforeAllianceChange  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnHitsBeforeAllianceChange; } 
  | StrategicNumberNameSnAllowCivilianDefense  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnAllowCivilianDefense; } 
  | StrategicNumberNameSnNumberForwardBuilders  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnNumberForwardBuilders; } 
  | StrategicNumberNameSnPercentAttackSoldiers  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnPercentAttackSoldiers; } 
  | StrategicNumberNameSnPercentAttackBoats  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnPercentAttackBoats; } 
  | StrategicNumberNameSnDoNotScaleForDifficultyLevel  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnDoNotScaleForDifficultyLevel; } 
  | StrategicNumberNameSnGroupFormDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnGroupFormDistance; } 
  | StrategicNumberNameSnIgnoreAttackGroupUnderAttack  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnIgnoreAttackGroupUnderAttack; } 
  | StrategicNumberNameSnGatherDefenseUnits  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnGatherDefenseUnits; } 
  | StrategicNumberNameSnMaximumWoodDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumWoodDropDistance; } 
  | StrategicNumberNameSnMaximumFoodDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumFoodDropDistance; } 
  | StrategicNumberNameSnMaximumHuntDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumHuntDropDistance; } 
  | StrategicNumberNameSnMaximumFishBoatDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumFishBoatDropDistance; } 
  | StrategicNumberNameSnMaximumGoldDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumGoldDropDistance; } 
  | StrategicNumberNameSnMaximumStoneDropDistance  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnMaximumStoneDropDistance; } 
  | StrategicNumberNameSnGatherIdleSoldiersAtCenter  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnGatherIdleSoldiersAtCenter; } 
  | StrategicNumberNameSnGarrisonRams  {}// static_cast<Condition*>(aiRule)->type = StrategicNumberName::SnGarrisonRams; } 

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
  | UnitMyEliteUniqueUnit  {}// static_cast<Condition*>(aiRule)->type = Unit::MyEliteUniqueUnit; } 
  | UnitMyUniqueUnit  {}// static_cast<Condition*>(aiRule)->type = Unit::MyUniqueUnit; } 
  | UnitMyUniqueUnitLine  {}// static_cast<Condition*>(aiRule)->type = Unit::MyUniqueUnitLine; } 

victoryconditionname:
    VictoryConditionNameStandard  {}// static_cast<Condition*>(aiRule)->type = VictoryConditionName::Standard; } 
  | VictoryConditionNameConquest  {}// static_cast<Condition*>(aiRule)->type = VictoryConditionName::Conquest; } 
  | VictoryConditionNameTimeLimit  {}// static_cast<Condition*>(aiRule)->type = VictoryConditionName::TimeLimit; } 
  | VictoryConditionNameScore  {}// static_cast<Condition*>(aiRule)->type = VictoryConditionName::Score; } 
  | VictoryConditionNameCustom  {}// static_cast<Condition*>(aiRule)->type = VictoryConditionName::Custom; } 

walltype:
    WallTypeFortifiedWall  {}// static_cast<Condition*>(aiRule)->type = WallType::FortifiedWall; } 
  | WallTypePalisadeWall  {}// static_cast<Condition*>(aiRule)->type = WallType::PalisadeWall; } 
  | WallTypeStoneWall  {}// static_cast<Condition*>(aiRule)->type = WallType::StoneWall; } 
  | WallTypeStoneWallLine  {}// static_cast<Condition*>(aiRule)->type = WallType::StoneWallLine; } 


symbolname:
fact   | age  | building  | civ  | commodity  | difficultylevel  | difficultyparameter  | diplomaticstance  | mapsizetype  | maptypename  | playernumbertype  | relop  | researchitem  | startingresourcestype  | strategicnumbername  | unit  | victoryconditionname  | walltype

acknowledgeevent:
    AcknowledgeEvent Number Number
acknowledgetaunt:
    AcknowledgeTaunt playernumber Number
attacknow:
    AttackNow
build:
    Build building
buildforward:
    BuildForward building
buildgate:
    BuildGate Number
buildwall:
    BuildWall Number walltype
buycommodity:
    BuyCommodity commodity
ccaddresource:
    CcAddResource commodity Number
chatlocal:
    ChatLocal String
chatlocaltoself:
    ChatLocalToSelf String
chatlocalusingid:
    ChatLocalUsingId Number
chatlocalusingrange:
    ChatLocalUsingRange Number Number
chattoall:
    ChatToAll String
chattoallusingid:
    ChatToAllUsingId Number
chattoallusingrange:
    ChatToAllUsingRange Number Number
chattoallies:
    ChatToAllies String
chattoalliesusingid:
    ChatToAlliesUsingId Number
chattoalliesusingrange:
    ChatToAlliesUsingRange Number Number
chattoenemies:
    ChatToEnemies String
chattoenemiesusingid:
    ChatToEnemiesUsingId Number
chattoenemiesusingrange:
    ChatToEnemiesUsingRange Number Number
chattoplayer:
    ChatToPlayer playernumber String
chattoplayerusingid:
    ChatToPlayerUsingId playernumber Number
chattoplayerusingrange:
    ChatToPlayerUsingRange playernumber Number Number
chattrace:
    ChatTrace Number
cleartributememory:
    ClearTributeMemory playernumber commodity
deletebuilding:
    DeleteBuilding building
deleteunit:
    DeleteUnit unit
disableself:
    DisableSelf
disabletimer:
    DisableTimer Number
donothing:
    DoNothing
enabletimer:
    EnableTimer Number Number
enablewallplacement:
    EnableWallPlacement Number
generaterandomnumber:
    GenerateRandomNumber Number
log:
    Log String
logtrace:
    LogTrace Number
releaseescrow:
    ReleaseEscrow commodity
research:
    Research age
    |  Research researchitem
resign:
    Resign
sellcommodity:
    SellCommodity commodity
setdifficultyparameter:
    SetDifficultyParameter difficultyparameter Number
setdoctrine:
    SetDoctrine Number
setescrowpercentage:
    SetEscrowPercentage commodity Number
setgoal:
    SetGoal Number Number
setsharedgoal:
    SetSharedGoal Number Number
setsignal:
    SetSignal Number
setstance:
    SetStance playernumber diplomaticstance
setstrategicnumber:
    SetStrategicNumber strategicnumbername Number
spy:
    Spy
taunt:
    Taunt Number
tauntusingrange:
    TauntUsingRange Number Number
train:
    Train unit
tributetoplayer:
    TributeToPlayer playernumber commodity Number

action:
    acknowledgeevent  | acknowledgetaunt  | attacknow  | build  | buildforward  | buildgate  | buildwall  | buycommodity  | ccaddresource  | chatlocal  | chatlocaltoself  | chatlocalusingid  | chatlocalusingrange  | chattoall  | chattoallusingid  | chattoallusingrange  | chattoallies  | chattoalliesusingid  | chattoalliesusingrange  | chattoenemies  | chattoenemiesusingid  | chattoenemiesusingrange  | chattoplayer  | chattoplayerusingid  | chattoplayerusingrange  | chattrace  | cleartributememory  | deletebuilding  | deleteunit  | disableself  | disabletimer  | donothing  | enabletimer  | enablewallplacement  | generaterandomnumber  | log  | logtrace  | releaseescrow  | research  | resign  | sellcommodity  | setdifficultyparameter  | setdoctrine  | setescrowpercentage  | setgoal  | setsharedgoal  | setsignal  | setstance  | setstrategicnumber  | spy  | taunt  | tauntusingrange  | train  | tributetoplayer

true:
    True

false:
    False

attacksoldiercount:
    AttackSoldierCount relop Number

attackwarboatcount:
    AttackWarboatCount relop Number

buildingavailable:
    BuildingAvailable building

buildingcount:
    BuildingCount relop Number

buildingcounttotal:
    BuildingCountTotal relop Number

buildingtypecount:
    BuildingTypeCount building relop Number

buildingtypecounttotal:
    BuildingTypeCountTotal building relop Number

canaffordbuilding:
    CanAffordBuilding building

canaffordcompletewall:
    CanAffordCompleteWall Number walltype

canaffordresearch:
    CanAffordResearch researchitem

canaffordunit:
    CanAffordUnit unit

canbuild:
    CanBuild building

canbuildgate:
    CanBuildGate Number

canbuildgatewithescrow:
    CanBuildGateWithEscrow Number

canbuildwall:
    CanBuildWall Number walltype

canbuildwallwithescrow:
    CanBuildWallWithEscrow Number walltype

canbuildwithescrow:
    CanBuildWithEscrow building

canbuycommodity:
    CanBuyCommodity commodity

canresearch:
    CanResearch researchitem

| CanResearch age

canresearchwithescrow:
    CanResearchWithEscrow researchitem

| CanResearchWithEscrow age

cansellcommodity:
    CanSellCommodity commodity

canspy:
    CanSpy

canspywithescrow:
    CanSpyWithEscrow

cantrain:
    CanTrain unit

cantrainwithescrow:
    CanTrainWithEscrow unit

ccplayersbuildingcount:
    CcPlayersBuildingCount playernumbertype relop Number

ccplayersbuildingtypecount:
    CcPlayersBuildingTypeCount playernumbertype building relop Number

ccplayersunitcount:
    CcPlayersUnitCount playernumbertype relop Number

ccplayersunittypecount:
    CcPlayersUnitTypeCount playernumbertype unit relop Number

cheatsenabled:
    CheatsEnabled

civselected:
    CivSelected civ

civilianpopulation:
    CivilianPopulation relop Number

commoditybuyingprice:
    CommodityBuyingPrice commodity relop Number

commoditysellingprice:
    CommoditySellingPrice commodity relop Number

currentage:
    CurrentAge relop age

currentagetime:
    CurrentAgeTime relop Number

currentscore:
    CurrentScore relop Number

deathmatchgame:
    DeathMatchGame

defendsoldiercount:
    DefendSoldierCount relop Number

defendwarboatcount:
    DefendWarboatCount relop Number

difficulty:
    Difficulty relop difficultylevel

doctrine:
    Doctrine Number

dropsitemindistance:
    DropsiteMinDistance commodity relop Number

enemybuildingsintown:
    EnemyBuildingsInTown

enemycapturedrelics:
    EnemyCapturedRelics

escrowamount:
    EscrowAmount commodity relop Number

eventdetected:
    EventDetected Number Number

foodamount:
    FoodAmount relop Number

gametime:
    GameTime relop Number

goal:
    Goal Number Number

goldamount:
    GoldAmount relop Number

housingheadroom:
    HousingHeadroom relop Number

idlefarmcount:
    IdleFarmCount relop Number

mapsize:
    MapSize mapsizetype

maptype:
    MapType maptypename

militarypopulation:
    MilitaryPopulation relop Number

playercomputer:
    PlayerComputer playernumbertype

playerhuman:
    PlayerHuman playernumbertype

playeringame:
    PlayerInGame playernumbertype

playernumber:
    PlayerNumber playernumbertype

playerresigned:
    PlayerResigned playernumbertype

playervalid:
    PlayerValid playernumbertype

playersbuildingcount:
    PlayersBuildingCount playernumbertype relop Number

playersbuildingtypecount:
    PlayersBuildingTypeCount playernumbertype building relop Number

playersciv:
    PlayersCiv playernumbertype civ

playerscivilianpopulation:
    PlayersCivilianPopulation playernumbertype relop Number

playerscurrentage:
    PlayersCurrentAge playernumbertype relop age

playerscurrentagetime:
    PlayersCurrentAgeTime playernumbertype relop Number

playersmilitarypopulation:
    PlayersMilitaryPopulation playernumbertype relop Number

playerspopulation:
    PlayersPopulation playernumbertype relop Number

playersscore:
    PlayersScore playernumbertype relop Number

playersstance:
    PlayersStance playernumbertype diplomaticstance

playerstribute:
    PlayersTribute playernumbertype commodity relop Number

playerstributememory:
    PlayersTributeMemory playernumbertype commodity relop Number

playersunitcount:
    PlayersUnitCount playernumbertype relop Number

playersunittypecount:
    PlayersUnitTypeCount playernumbertype unit relop Number

population:
    Population relop Number

populationcap:
    PopulationCap relop Number

populationheadroom:
    PopulationHeadroom relop Number

randomnumber:
    RandomNumber relop Number

regicidegame:
    RegicideGame

researchavailable:
    ResearchAvailable researchitem

researchcompleted:
    ResearchCompleted researchitem

resourcefound:
    ResourceFound commodity

sharedgoal:
    SharedGoal Number Number

sheepandforagetoofar:
    SheepAndForageTooFar

soldiercount:
    SoldierCount relop Number

stancetoward:
    StanceToward playernumbertype diplomaticstance

startingage:
    StartingAge relop age

startingresources:
    StartingResources relop startingresourcestype

stoneamount:
    StoneAmount relop Number

strategicnumber:
    StrategicNumber strategicnumbername relop Number

tauntdetected:
    TauntDetected playernumbertype Number

timertriggered:
    TimerTriggered Number

townunderattack:
    TownUnderAttack

unitavailable:
    UnitAvailable unit

unitcount:
    UnitCount relop Number

unitcounttotal:
    UnitCountTotal relop Number

unittypecount:
    UnitTypeCount unit relop Number

unittypecounttotal:
    UnitTypeCountTotal unit relop Number

victorycondition:
    VictoryCondition victoryconditionname

wallcompletedpercentage:
    WallCompletedPercentage Number relop Number

wallinvisiblepercentage:
    WallInvisiblePercentage Number relop Number

warboatcount:
    WarboatCount relop Number

woodamount:
    WoodAmount relop Number

fact:
    true  | false  | attacksoldiercount  | attackwarboatcount  | buildingavailable  | buildingcount  | buildingcounttotal  | buildingtypecount  | buildingtypecounttotal  | canaffordbuilding  | canaffordcompletewall  | canaffordresearch  | canaffordunit  | canbuild  | canbuildgate  | canbuildgatewithescrow  | canbuildwall  | canbuildwallwithescrow  | canbuildwithescrow  | canbuycommodity  | canresearch  | canresearchwithescrow  | cansellcommodity  | canspy  | canspywithescrow  | cantrain  | cantrainwithescrow  | ccplayersbuildingcount  | ccplayersbuildingtypecount  | ccplayersunitcount  | ccplayersunittypecount  | cheatsenabled  | civselected  | civilianpopulation  | commoditybuyingprice  | commoditysellingprice  | currentage  | currentagetime  | currentscore  | deathmatchgame  | defendsoldiercount  | defendwarboatcount  | difficulty  | doctrine  | dropsitemindistance  | enemybuildingsintown  | enemycapturedrelics  | escrowamount  | eventdetected  | foodamount  | gametime  | goal  | goldamount  | housingheadroom  | idlefarmcount  | mapsize  | maptype  | militarypopulation  | playercomputer  | playerhuman  | playeringame  | playernumber  | playerresigned  | playervalid  | playersbuildingcount  | playersbuildingtypecount  | playersciv  | playerscivilianpopulation  | playerscurrentage  | playerscurrentagetime  | playersmilitarypopulation  | playerspopulation  | playersscore  | playersstance  | playerstribute  | playerstributememory  | playersunitcount  | playersunittypecount  | population  | populationcap  | populationheadroom  | randomnumber  | regicidegame  | researchavailable  | researchcompleted  | resourcefound  | sharedgoal  | sheepandforagetoofar  | soldiercount  | stancetoward  | startingage  | startingresources  | stoneamount  | strategicnumber  | tauntdetected  | timertriggered  | townunderattack  | unitavailable  | unitcount  | unitcounttotal  | unittypecount  | unittypecounttotal  | victorycondition  | wallcompletedpercentage  | wallinvisiblepercentage  | warboatcount  | woodamount

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
