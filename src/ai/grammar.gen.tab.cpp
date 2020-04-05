// A Bison parser, made by GNU Bison 3.5.3.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.



// First part of user prologue.
#line 1 "grammar.gen.ypp"

    #include "gen/enums.h"
#line 40 "grammar.gen.ypp"

    #include <cassert>
    #include <fstream>
    #include <iostream>

    #include "ScriptLoader.h"
    #include "ScriptTokenizer.h"

    #include "grammar.gen.tab.hpp"
    #include "location.hh"

    #undef yylex
    #define yylex scanner.yylex

#line 58 "grammar.gen.tab.cpp"


#include "grammar.gen.tab.hpp"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 9 "grammar.gen.ypp"
namespace  ai  {
#line 155 "grammar.gen.tab.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  ScriptParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  ScriptParser::ScriptParser (ai::ScriptLoader &driver_yyarg, ai::ScriptTokenizer &scanner_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg),
      scanner (scanner_yyarg)
  {}

  ScriptParser::~ScriptParser ()
  {}

  ScriptParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  ScriptParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  ScriptParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  ScriptParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  ScriptParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  ScriptParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  ScriptParser::symbol_number_type
  ScriptParser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  ScriptParser::stack_symbol_type::stack_symbol_type ()
  {}

  ScriptParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 17: // AcknowledgeEvent
      case 18: // AcknowledgeTaunt
      case 24: // AttackNow
      case 27: // Build
      case 28: // BuildForward
      case 29: // BuildGate
      case 59: // BuildWall
      case 60: // BuyCommodity
      case 79: // CcAddResource
      case 84: // ChatLocal
      case 85: // ChatLocalToSelf
      case 86: // ChatLocalUsingId
      case 87: // ChatLocalUsingRange
      case 88: // ChatToAll
      case 89: // ChatToAllies
      case 90: // ChatToAlliesUsingId
      case 91: // ChatToAlliesUsingRange
      case 92: // ChatToAllUsingId
      case 93: // ChatToAllUsingRange
      case 94: // ChatToEnemies
      case 95: // ChatToEnemiesUsingId
      case 96: // ChatToEnemiesUsingRange
      case 97: // ChatToPlayer
      case 98: // ChatToPlayerUsingId
      case 99: // ChatToPlayerUsingRange
      case 100: // ChatTrace
      case 118: // ClearTributeMemory
      case 131: // DeleteBuilding
      case 132: // DeleteUnit
      case 144: // DisableSelf
      case 145: // DisableTimer
      case 147: // DoNothing
      case 149: // EnableTimer
      case 150: // EnableWallPlacement
      case 158: // GenerateRandomNumber
      case 163: // Log
      case 164: // LogTrace
      case 232: // ReleaseEscrow
      case 239: // Research
      case 359: // Resign
      case 361: // SellCommodity
      case 362: // SetDifficultyParameter
      case 363: // SetDoctrine
      case 364: // SetEscrowPercentage
      case 365: // SetGoal
      case 366: // SetSharedGoal
      case 367: // SetSignal
      case 368: // SetStance
      case 369: // SetStrategicNumber
      case 373: // Spy
      case 514: // Taunt
      case 516: // TauntUsingRange
      case 519: // Train
      case 520: // TributeToPlayer
        value.YY_MOVE_OR_COPY< ActionType > (YY_MOVE (that.value));
        break;

      case 682: // age
        value.YY_MOVE_OR_COPY< Age > (YY_MOVE (that.value));
        break;

      case 683: // building
        value.YY_MOVE_OR_COPY< Building > (YY_MOVE (that.value));
        break;

      case 684: // civ
        value.YY_MOVE_OR_COPY< Civ > (YY_MOVE (that.value));
        break;

      case 685: // commodity
        value.YY_MOVE_OR_COPY< Commodity > (YY_MOVE (that.value));
        break;

      case 686: // difficultylevel
        value.YY_MOVE_OR_COPY< DifficultyLevel > (YY_MOVE (that.value));
        break;

      case 687: // difficultyparameter
        value.YY_MOVE_OR_COPY< DifficultyParameter > (YY_MOVE (that.value));
        break;

      case 688: // diplomaticstance
        value.YY_MOVE_OR_COPY< DiplomaticStance > (YY_MOVE (that.value));
        break;

      case 25: // AttackSoldierCount
      case 26: // AttackWarboatCount
      case 54: // BuildingAvailable
      case 55: // BuildingCount
      case 56: // BuildingCountTotal
      case 57: // BuildingTypeCount
      case 58: // BuildingTypeCountTotal
      case 61: // CanAffordBuilding
      case 62: // CanAffordCompleteWall
      case 63: // CanAffordResearch
      case 64: // CanAffordUnit
      case 65: // CanBuild
      case 66: // CanBuildGate
      case 67: // CanBuildGateWithEscrow
      case 68: // CanBuildWall
      case 69: // CanBuildWallWithEscrow
      case 70: // CanBuildWithEscrow
      case 71: // CanBuyCommodity
      case 72: // CanResearch
      case 73: // CanResearchWithEscrow
      case 74: // CanSellCommodity
      case 75: // CanSpy
      case 76: // CanSpyWithEscrow
      case 77: // CanTrain
      case 78: // CanTrainWithEscrow
      case 80: // CcPlayersBuildingCount
      case 81: // CcPlayersBuildingTypeCount
      case 82: // CcPlayersUnitCount
      case 83: // CcPlayersUnitTypeCount
      case 101: // CheatsEnabled
      case 116: // CivilianPopulation
      case 117: // CivSelected
      case 119: // CommodityBuyingPrice
      case 124: // CommoditySellingPrice
      case 125: // CurrentAge
      case 126: // CurrentAgeTime
      case 127: // CurrentScore
      case 128: // DeathMatchGame
      case 129: // DefendSoldierCount
      case 130: // DefendWarboatCount
      case 133: // Difficulty
      case 146: // Doctrine
      case 148: // DropsiteMinDistance
      case 151: // EnemyBuildingsInTown
      case 152: // EnemyCapturedRelics
      case 153: // EscrowAmount
      case 154: // EventDetected
      case 155: // Falseval
      case 156: // FoodAmount
      case 157: // GameTime
      case 159: // Goal
      case 160: // GoldAmount
      case 161: // HousingHeadroom
      case 162: // IdleFarmCount
      case 165: // MapSize
      case 172: // MapType
      case 189: // MilitaryPopulation
      case 190: // PlayerComputer
      case 191: // PlayerHuman
      case 192: // PlayerInGame
      case 193: // PlayerNumber
      case 211: // PlayerResigned
      case 212: // PlayersBuildingCount
      case 213: // PlayersBuildingTypeCount
      case 214: // PlayersCiv
      case 215: // PlayersCivilianPopulation
      case 216: // PlayersCurrentAge
      case 217: // PlayersCurrentAgeTime
      case 218: // PlayersMilitaryPopulation
      case 219: // PlayersPopulation
      case 220: // PlayersScore
      case 221: // PlayersStance
      case 222: // PlayersTribute
      case 223: // PlayersTributeMemory
      case 224: // PlayersUnitCount
      case 225: // PlayersUnitTypeCount
      case 226: // PlayerValid
      case 227: // Population
      case 228: // PopulationCap
      case 229: // PopulationHeadroom
      case 230: // RandomNumber
      case 231: // RegicideGame
      case 240: // ResearchAvailable
      case 241: // ResearchCompleted
      case 360: // ResourceFound
      case 370: // SharedGoal
      case 371: // SheepAndForageTooFar
      case 372: // SoldierCount
      case 374: // StanceToward
      case 375: // StartingAge
      case 376: // StartingResources
      case 380: // StoneAmount
      case 381: // StrategicNumber
      case 515: // TauntDetected
      case 517: // TimerTriggered
      case 518: // TownUnderAttack
      case 521: // Trueval
      case 654: // UnitAvailable
      case 655: // UnitCount
      case 656: // UnitCountTotal
      case 657: // UnitTypeCount
      case 658: // UnitTypeCountTotal
      case 659: // VictoryCondition
      case 665: // WallCompletedPercentage
      case 666: // WallInvisiblePercentage
      case 671: // WarboatCount
      case 672: // WoodAmount
        value.YY_MOVE_OR_COPY< Fact > (YY_MOVE (that.value));
        break;

      case 689: // mapsizetype
        value.YY_MOVE_OR_COPY< MapSizeType > (YY_MOVE (that.value));
        break;

      case 690: // maptypename
        value.YY_MOVE_OR_COPY< MapTypeName > (YY_MOVE (that.value));
        break;

      case 691: // playernumbertype
        value.YY_MOVE_OR_COPY< PlayerNumberType > (YY_MOVE (that.value));
        break;

      case 692: // relop
        value.YY_MOVE_OR_COPY< RelOp > (YY_MOVE (that.value));
        break;

      case 693: // researchitem
        value.YY_MOVE_OR_COPY< ResearchItem > (YY_MOVE (that.value));
        break;

      case 694: // startingresourcestype
        value.YY_MOVE_OR_COPY< StartingResourcesType > (YY_MOVE (that.value));
        break;

      case 695: // strategicnumbername
        value.YY_MOVE_OR_COPY< StrategicNumberName > (YY_MOVE (that.value));
        break;

      case 696: // unit
        value.YY_MOVE_OR_COPY< Unit > (YY_MOVE (that.value));
        break;

      case 697: // victoryconditionname
        value.YY_MOVE_OR_COPY< VictoryConditionName > (YY_MOVE (that.value));
        break;

      case 698: // walltype
        value.YY_MOVE_OR_COPY< WallType > (YY_MOVE (that.value));
        break;

      case 3: // Number
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 681: // singleaction
      case 699: // acknowledgeevent
      case 700: // acknowledgetaunt
      case 701: // attacknow
      case 702: // build
      case 703: // buildforward
      case 704: // buildgate
      case 705: // buildwall
      case 706: // buycommodity
      case 707: // ccaddresource
      case 708: // chatlocal
      case 709: // chatlocaltoself
      case 710: // chatlocalusingid
      case 711: // chatlocalusingrange
      case 712: // chattoall
      case 713: // chattoallusingid
      case 714: // chattoallusingrange
      case 715: // chattoallies
      case 716: // chattoalliesusingid
      case 717: // chattoalliesusingrange
      case 718: // chattoenemies
      case 719: // chattoenemiesusingid
      case 720: // chattoenemiesusingrange
      case 721: // chattoplayer
      case 722: // chattoplayerusingid
      case 723: // chattoplayerusingrange
      case 724: // chattrace
      case 725: // cleartributememory
      case 726: // deletebuilding
      case 727: // deleteunit
      case 728: // disableself
      case 729: // disabletimer
      case 730: // donothing
      case 731: // enabletimer
      case 732: // enablewallplacement
      case 733: // generaterandomnumber
      case 734: // log
      case 735: // logtrace
      case 736: // releaseescrow
      case 737: // research
      case 738: // resign
      case 739: // sellcommodity
      case 740: // setdifficultyparameter
      case 741: // setdoctrine
      case 742: // setescrowpercentage
      case 743: // setgoal
      case 744: // setsharedgoal
      case 745: // setsignal
      case 746: // setstance
      case 747: // setstrategicnumber
      case 748: // spy
      case 749: // taunt
      case 750: // tauntusingrange
      case 751: // train
      case 752: // tributetoplayer
      case 753: // action
        value.YY_MOVE_OR_COPY< std::shared_ptr<ai::Action> > (YY_MOVE (that.value));
        break;

      case 676: // rule
        value.YY_MOVE_OR_COPY< std::shared_ptr<ai::AiRule> > (YY_MOVE (that.value));
        break;

      case 678: // condition
      case 679: // conditiontype
      case 754: // trueval
      case 755: // falseval
      case 756: // attacksoldiercount
      case 757: // attackwarboatcount
      case 758: // buildingavailable
      case 759: // buildingcount
      case 760: // buildingcounttotal
      case 761: // buildingtypecount
      case 762: // buildingtypecounttotal
      case 763: // canaffordbuilding
      case 764: // canaffordcompletewall
      case 765: // canaffordresearch
      case 766: // canaffordunit
      case 767: // canbuild
      case 768: // canbuildgate
      case 769: // canbuildgatewithescrow
      case 770: // canbuildwall
      case 771: // canbuildwallwithescrow
      case 772: // canbuildwithescrow
      case 773: // canbuycommodity
      case 774: // canresearch
      case 775: // canresearchwithescrow
      case 776: // cansellcommodity
      case 777: // canspy
      case 778: // canspywithescrow
      case 779: // cantrain
      case 780: // cantrainwithescrow
      case 781: // ccplayersbuildingcount
      case 782: // ccplayersbuildingtypecount
      case 783: // ccplayersunitcount
      case 784: // ccplayersunittypecount
      case 785: // cheatsenabled
      case 786: // civselected
      case 787: // civilianpopulation
      case 788: // commoditybuyingprice
      case 789: // commoditysellingprice
      case 790: // currentage
      case 791: // currentagetime
      case 792: // currentscore
      case 793: // deathmatchgame
      case 794: // defendsoldiercount
      case 795: // defendwarboatcount
      case 796: // difficulty
      case 797: // doctrine
      case 798: // dropsitemindistance
      case 799: // enemybuildingsintown
      case 800: // enemycapturedrelics
      case 801: // escrowamount
      case 802: // eventdetected
      case 803: // foodamount
      case 804: // gametime
      case 805: // goal
      case 806: // goldamount
      case 807: // housingheadroom
      case 808: // idlefarmcount
      case 809: // mapsize
      case 810: // maptype
      case 811: // militarypopulation
      case 812: // playercomputer
      case 813: // playerhuman
      case 814: // playeringame
      case 815: // playernumber
      case 816: // playerresigned
      case 817: // playervalid
      case 818: // playersbuildingcount
      case 819: // playersbuildingtypecount
      case 820: // playersciv
      case 821: // playerscivilianpopulation
      case 822: // playerscurrentage
      case 823: // playerscurrentagetime
      case 824: // playersmilitarypopulation
      case 825: // playerspopulation
      case 826: // playersscore
      case 827: // playersstance
      case 828: // playerstribute
      case 829: // playerstributememory
      case 830: // playersunitcount
      case 831: // playersunittypecount
      case 832: // population
      case 833: // populationcap
      case 834: // populationheadroom
      case 835: // randomnumber
      case 836: // regicidegame
      case 837: // researchavailable
      case 838: // researchcompleted
      case 839: // resourcefound
      case 840: // sharedgoal
      case 841: // sheepandforagetoofar
      case 842: // soldiercount
      case 843: // stancetoward
      case 844: // startingage
      case 845: // startingresources
      case 846: // stoneamount
      case 847: // strategicnumber
      case 848: // tauntdetected
      case 849: // timertriggered
      case 850: // townunderattack
      case 851: // unitavailable
      case 852: // unitcount
      case 853: // unitcounttotal
      case 854: // unittypecount
      case 855: // unittypecounttotal
      case 856: // victorycondition
      case 857: // wallcompletedpercentage
      case 858: // wallinvisiblepercentage
      case 859: // warboatcount
      case 860: // woodamount
      case 861: // fact
        value.YY_MOVE_OR_COPY< std::shared_ptr<ai::Condition> > (YY_MOVE (that.value));
        break;

      case 4: // String
      case 5: // SymbolName
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 680: // actions
        value.YY_MOVE_OR_COPY< std::vector<std::shared_ptr<ai::Action>> > (YY_MOVE (that.value));
        break;

      case 677: // conditions
        value.YY_MOVE_OR_COPY< std::vector<std::shared_ptr<ai::Condition>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  ScriptParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 17: // AcknowledgeEvent
      case 18: // AcknowledgeTaunt
      case 24: // AttackNow
      case 27: // Build
      case 28: // BuildForward
      case 29: // BuildGate
      case 59: // BuildWall
      case 60: // BuyCommodity
      case 79: // CcAddResource
      case 84: // ChatLocal
      case 85: // ChatLocalToSelf
      case 86: // ChatLocalUsingId
      case 87: // ChatLocalUsingRange
      case 88: // ChatToAll
      case 89: // ChatToAllies
      case 90: // ChatToAlliesUsingId
      case 91: // ChatToAlliesUsingRange
      case 92: // ChatToAllUsingId
      case 93: // ChatToAllUsingRange
      case 94: // ChatToEnemies
      case 95: // ChatToEnemiesUsingId
      case 96: // ChatToEnemiesUsingRange
      case 97: // ChatToPlayer
      case 98: // ChatToPlayerUsingId
      case 99: // ChatToPlayerUsingRange
      case 100: // ChatTrace
      case 118: // ClearTributeMemory
      case 131: // DeleteBuilding
      case 132: // DeleteUnit
      case 144: // DisableSelf
      case 145: // DisableTimer
      case 147: // DoNothing
      case 149: // EnableTimer
      case 150: // EnableWallPlacement
      case 158: // GenerateRandomNumber
      case 163: // Log
      case 164: // LogTrace
      case 232: // ReleaseEscrow
      case 239: // Research
      case 359: // Resign
      case 361: // SellCommodity
      case 362: // SetDifficultyParameter
      case 363: // SetDoctrine
      case 364: // SetEscrowPercentage
      case 365: // SetGoal
      case 366: // SetSharedGoal
      case 367: // SetSignal
      case 368: // SetStance
      case 369: // SetStrategicNumber
      case 373: // Spy
      case 514: // Taunt
      case 516: // TauntUsingRange
      case 519: // Train
      case 520: // TributeToPlayer
        value.move< ActionType > (YY_MOVE (that.value));
        break;

      case 682: // age
        value.move< Age > (YY_MOVE (that.value));
        break;

      case 683: // building
        value.move< Building > (YY_MOVE (that.value));
        break;

      case 684: // civ
        value.move< Civ > (YY_MOVE (that.value));
        break;

      case 685: // commodity
        value.move< Commodity > (YY_MOVE (that.value));
        break;

      case 686: // difficultylevel
        value.move< DifficultyLevel > (YY_MOVE (that.value));
        break;

      case 687: // difficultyparameter
        value.move< DifficultyParameter > (YY_MOVE (that.value));
        break;

      case 688: // diplomaticstance
        value.move< DiplomaticStance > (YY_MOVE (that.value));
        break;

      case 25: // AttackSoldierCount
      case 26: // AttackWarboatCount
      case 54: // BuildingAvailable
      case 55: // BuildingCount
      case 56: // BuildingCountTotal
      case 57: // BuildingTypeCount
      case 58: // BuildingTypeCountTotal
      case 61: // CanAffordBuilding
      case 62: // CanAffordCompleteWall
      case 63: // CanAffordResearch
      case 64: // CanAffordUnit
      case 65: // CanBuild
      case 66: // CanBuildGate
      case 67: // CanBuildGateWithEscrow
      case 68: // CanBuildWall
      case 69: // CanBuildWallWithEscrow
      case 70: // CanBuildWithEscrow
      case 71: // CanBuyCommodity
      case 72: // CanResearch
      case 73: // CanResearchWithEscrow
      case 74: // CanSellCommodity
      case 75: // CanSpy
      case 76: // CanSpyWithEscrow
      case 77: // CanTrain
      case 78: // CanTrainWithEscrow
      case 80: // CcPlayersBuildingCount
      case 81: // CcPlayersBuildingTypeCount
      case 82: // CcPlayersUnitCount
      case 83: // CcPlayersUnitTypeCount
      case 101: // CheatsEnabled
      case 116: // CivilianPopulation
      case 117: // CivSelected
      case 119: // CommodityBuyingPrice
      case 124: // CommoditySellingPrice
      case 125: // CurrentAge
      case 126: // CurrentAgeTime
      case 127: // CurrentScore
      case 128: // DeathMatchGame
      case 129: // DefendSoldierCount
      case 130: // DefendWarboatCount
      case 133: // Difficulty
      case 146: // Doctrine
      case 148: // DropsiteMinDistance
      case 151: // EnemyBuildingsInTown
      case 152: // EnemyCapturedRelics
      case 153: // EscrowAmount
      case 154: // EventDetected
      case 155: // Falseval
      case 156: // FoodAmount
      case 157: // GameTime
      case 159: // Goal
      case 160: // GoldAmount
      case 161: // HousingHeadroom
      case 162: // IdleFarmCount
      case 165: // MapSize
      case 172: // MapType
      case 189: // MilitaryPopulation
      case 190: // PlayerComputer
      case 191: // PlayerHuman
      case 192: // PlayerInGame
      case 193: // PlayerNumber
      case 211: // PlayerResigned
      case 212: // PlayersBuildingCount
      case 213: // PlayersBuildingTypeCount
      case 214: // PlayersCiv
      case 215: // PlayersCivilianPopulation
      case 216: // PlayersCurrentAge
      case 217: // PlayersCurrentAgeTime
      case 218: // PlayersMilitaryPopulation
      case 219: // PlayersPopulation
      case 220: // PlayersScore
      case 221: // PlayersStance
      case 222: // PlayersTribute
      case 223: // PlayersTributeMemory
      case 224: // PlayersUnitCount
      case 225: // PlayersUnitTypeCount
      case 226: // PlayerValid
      case 227: // Population
      case 228: // PopulationCap
      case 229: // PopulationHeadroom
      case 230: // RandomNumber
      case 231: // RegicideGame
      case 240: // ResearchAvailable
      case 241: // ResearchCompleted
      case 360: // ResourceFound
      case 370: // SharedGoal
      case 371: // SheepAndForageTooFar
      case 372: // SoldierCount
      case 374: // StanceToward
      case 375: // StartingAge
      case 376: // StartingResources
      case 380: // StoneAmount
      case 381: // StrategicNumber
      case 515: // TauntDetected
      case 517: // TimerTriggered
      case 518: // TownUnderAttack
      case 521: // Trueval
      case 654: // UnitAvailable
      case 655: // UnitCount
      case 656: // UnitCountTotal
      case 657: // UnitTypeCount
      case 658: // UnitTypeCountTotal
      case 659: // VictoryCondition
      case 665: // WallCompletedPercentage
      case 666: // WallInvisiblePercentage
      case 671: // WarboatCount
      case 672: // WoodAmount
        value.move< Fact > (YY_MOVE (that.value));
        break;

      case 689: // mapsizetype
        value.move< MapSizeType > (YY_MOVE (that.value));
        break;

      case 690: // maptypename
        value.move< MapTypeName > (YY_MOVE (that.value));
        break;

      case 691: // playernumbertype
        value.move< PlayerNumberType > (YY_MOVE (that.value));
        break;

      case 692: // relop
        value.move< RelOp > (YY_MOVE (that.value));
        break;

      case 693: // researchitem
        value.move< ResearchItem > (YY_MOVE (that.value));
        break;

      case 694: // startingresourcestype
        value.move< StartingResourcesType > (YY_MOVE (that.value));
        break;

      case 695: // strategicnumbername
        value.move< StrategicNumberName > (YY_MOVE (that.value));
        break;

      case 696: // unit
        value.move< Unit > (YY_MOVE (that.value));
        break;

      case 697: // victoryconditionname
        value.move< VictoryConditionName > (YY_MOVE (that.value));
        break;

      case 698: // walltype
        value.move< WallType > (YY_MOVE (that.value));
        break;

      case 3: // Number
        value.move< int > (YY_MOVE (that.value));
        break;

      case 681: // singleaction
      case 699: // acknowledgeevent
      case 700: // acknowledgetaunt
      case 701: // attacknow
      case 702: // build
      case 703: // buildforward
      case 704: // buildgate
      case 705: // buildwall
      case 706: // buycommodity
      case 707: // ccaddresource
      case 708: // chatlocal
      case 709: // chatlocaltoself
      case 710: // chatlocalusingid
      case 711: // chatlocalusingrange
      case 712: // chattoall
      case 713: // chattoallusingid
      case 714: // chattoallusingrange
      case 715: // chattoallies
      case 716: // chattoalliesusingid
      case 717: // chattoalliesusingrange
      case 718: // chattoenemies
      case 719: // chattoenemiesusingid
      case 720: // chattoenemiesusingrange
      case 721: // chattoplayer
      case 722: // chattoplayerusingid
      case 723: // chattoplayerusingrange
      case 724: // chattrace
      case 725: // cleartributememory
      case 726: // deletebuilding
      case 727: // deleteunit
      case 728: // disableself
      case 729: // disabletimer
      case 730: // donothing
      case 731: // enabletimer
      case 732: // enablewallplacement
      case 733: // generaterandomnumber
      case 734: // log
      case 735: // logtrace
      case 736: // releaseescrow
      case 737: // research
      case 738: // resign
      case 739: // sellcommodity
      case 740: // setdifficultyparameter
      case 741: // setdoctrine
      case 742: // setescrowpercentage
      case 743: // setgoal
      case 744: // setsharedgoal
      case 745: // setsignal
      case 746: // setstance
      case 747: // setstrategicnumber
      case 748: // spy
      case 749: // taunt
      case 750: // tauntusingrange
      case 751: // train
      case 752: // tributetoplayer
      case 753: // action
        value.move< std::shared_ptr<ai::Action> > (YY_MOVE (that.value));
        break;

      case 676: // rule
        value.move< std::shared_ptr<ai::AiRule> > (YY_MOVE (that.value));
        break;

      case 678: // condition
      case 679: // conditiontype
      case 754: // trueval
      case 755: // falseval
      case 756: // attacksoldiercount
      case 757: // attackwarboatcount
      case 758: // buildingavailable
      case 759: // buildingcount
      case 760: // buildingcounttotal
      case 761: // buildingtypecount
      case 762: // buildingtypecounttotal
      case 763: // canaffordbuilding
      case 764: // canaffordcompletewall
      case 765: // canaffordresearch
      case 766: // canaffordunit
      case 767: // canbuild
      case 768: // canbuildgate
      case 769: // canbuildgatewithescrow
      case 770: // canbuildwall
      case 771: // canbuildwallwithescrow
      case 772: // canbuildwithescrow
      case 773: // canbuycommodity
      case 774: // canresearch
      case 775: // canresearchwithescrow
      case 776: // cansellcommodity
      case 777: // canspy
      case 778: // canspywithescrow
      case 779: // cantrain
      case 780: // cantrainwithescrow
      case 781: // ccplayersbuildingcount
      case 782: // ccplayersbuildingtypecount
      case 783: // ccplayersunitcount
      case 784: // ccplayersunittypecount
      case 785: // cheatsenabled
      case 786: // civselected
      case 787: // civilianpopulation
      case 788: // commoditybuyingprice
      case 789: // commoditysellingprice
      case 790: // currentage
      case 791: // currentagetime
      case 792: // currentscore
      case 793: // deathmatchgame
      case 794: // defendsoldiercount
      case 795: // defendwarboatcount
      case 796: // difficulty
      case 797: // doctrine
      case 798: // dropsitemindistance
      case 799: // enemybuildingsintown
      case 800: // enemycapturedrelics
      case 801: // escrowamount
      case 802: // eventdetected
      case 803: // foodamount
      case 804: // gametime
      case 805: // goal
      case 806: // goldamount
      case 807: // housingheadroom
      case 808: // idlefarmcount
      case 809: // mapsize
      case 810: // maptype
      case 811: // militarypopulation
      case 812: // playercomputer
      case 813: // playerhuman
      case 814: // playeringame
      case 815: // playernumber
      case 816: // playerresigned
      case 817: // playervalid
      case 818: // playersbuildingcount
      case 819: // playersbuildingtypecount
      case 820: // playersciv
      case 821: // playerscivilianpopulation
      case 822: // playerscurrentage
      case 823: // playerscurrentagetime
      case 824: // playersmilitarypopulation
      case 825: // playerspopulation
      case 826: // playersscore
      case 827: // playersstance
      case 828: // playerstribute
      case 829: // playerstributememory
      case 830: // playersunitcount
      case 831: // playersunittypecount
      case 832: // population
      case 833: // populationcap
      case 834: // populationheadroom
      case 835: // randomnumber
      case 836: // regicidegame
      case 837: // researchavailable
      case 838: // researchcompleted
      case 839: // resourcefound
      case 840: // sharedgoal
      case 841: // sheepandforagetoofar
      case 842: // soldiercount
      case 843: // stancetoward
      case 844: // startingage
      case 845: // startingresources
      case 846: // stoneamount
      case 847: // strategicnumber
      case 848: // tauntdetected
      case 849: // timertriggered
      case 850: // townunderattack
      case 851: // unitavailable
      case 852: // unitcount
      case 853: // unitcounttotal
      case 854: // unittypecount
      case 855: // unittypecounttotal
      case 856: // victorycondition
      case 857: // wallcompletedpercentage
      case 858: // wallinvisiblepercentage
      case 859: // warboatcount
      case 860: // woodamount
      case 861: // fact
        value.move< std::shared_ptr<ai::Condition> > (YY_MOVE (that.value));
        break;

      case 4: // String
      case 5: // SymbolName
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 680: // actions
        value.move< std::vector<std::shared_ptr<ai::Action>> > (YY_MOVE (that.value));
        break;

      case 677: // conditions
        value.move< std::vector<std::shared_ptr<ai::Condition>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  ScriptParser::stack_symbol_type&
  ScriptParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 17: // AcknowledgeEvent
      case 18: // AcknowledgeTaunt
      case 24: // AttackNow
      case 27: // Build
      case 28: // BuildForward
      case 29: // BuildGate
      case 59: // BuildWall
      case 60: // BuyCommodity
      case 79: // CcAddResource
      case 84: // ChatLocal
      case 85: // ChatLocalToSelf
      case 86: // ChatLocalUsingId
      case 87: // ChatLocalUsingRange
      case 88: // ChatToAll
      case 89: // ChatToAllies
      case 90: // ChatToAlliesUsingId
      case 91: // ChatToAlliesUsingRange
      case 92: // ChatToAllUsingId
      case 93: // ChatToAllUsingRange
      case 94: // ChatToEnemies
      case 95: // ChatToEnemiesUsingId
      case 96: // ChatToEnemiesUsingRange
      case 97: // ChatToPlayer
      case 98: // ChatToPlayerUsingId
      case 99: // ChatToPlayerUsingRange
      case 100: // ChatTrace
      case 118: // ClearTributeMemory
      case 131: // DeleteBuilding
      case 132: // DeleteUnit
      case 144: // DisableSelf
      case 145: // DisableTimer
      case 147: // DoNothing
      case 149: // EnableTimer
      case 150: // EnableWallPlacement
      case 158: // GenerateRandomNumber
      case 163: // Log
      case 164: // LogTrace
      case 232: // ReleaseEscrow
      case 239: // Research
      case 359: // Resign
      case 361: // SellCommodity
      case 362: // SetDifficultyParameter
      case 363: // SetDoctrine
      case 364: // SetEscrowPercentage
      case 365: // SetGoal
      case 366: // SetSharedGoal
      case 367: // SetSignal
      case 368: // SetStance
      case 369: // SetStrategicNumber
      case 373: // Spy
      case 514: // Taunt
      case 516: // TauntUsingRange
      case 519: // Train
      case 520: // TributeToPlayer
        value.copy< ActionType > (that.value);
        break;

      case 682: // age
        value.copy< Age > (that.value);
        break;

      case 683: // building
        value.copy< Building > (that.value);
        break;

      case 684: // civ
        value.copy< Civ > (that.value);
        break;

      case 685: // commodity
        value.copy< Commodity > (that.value);
        break;

      case 686: // difficultylevel
        value.copy< DifficultyLevel > (that.value);
        break;

      case 687: // difficultyparameter
        value.copy< DifficultyParameter > (that.value);
        break;

      case 688: // diplomaticstance
        value.copy< DiplomaticStance > (that.value);
        break;

      case 25: // AttackSoldierCount
      case 26: // AttackWarboatCount
      case 54: // BuildingAvailable
      case 55: // BuildingCount
      case 56: // BuildingCountTotal
      case 57: // BuildingTypeCount
      case 58: // BuildingTypeCountTotal
      case 61: // CanAffordBuilding
      case 62: // CanAffordCompleteWall
      case 63: // CanAffordResearch
      case 64: // CanAffordUnit
      case 65: // CanBuild
      case 66: // CanBuildGate
      case 67: // CanBuildGateWithEscrow
      case 68: // CanBuildWall
      case 69: // CanBuildWallWithEscrow
      case 70: // CanBuildWithEscrow
      case 71: // CanBuyCommodity
      case 72: // CanResearch
      case 73: // CanResearchWithEscrow
      case 74: // CanSellCommodity
      case 75: // CanSpy
      case 76: // CanSpyWithEscrow
      case 77: // CanTrain
      case 78: // CanTrainWithEscrow
      case 80: // CcPlayersBuildingCount
      case 81: // CcPlayersBuildingTypeCount
      case 82: // CcPlayersUnitCount
      case 83: // CcPlayersUnitTypeCount
      case 101: // CheatsEnabled
      case 116: // CivilianPopulation
      case 117: // CivSelected
      case 119: // CommodityBuyingPrice
      case 124: // CommoditySellingPrice
      case 125: // CurrentAge
      case 126: // CurrentAgeTime
      case 127: // CurrentScore
      case 128: // DeathMatchGame
      case 129: // DefendSoldierCount
      case 130: // DefendWarboatCount
      case 133: // Difficulty
      case 146: // Doctrine
      case 148: // DropsiteMinDistance
      case 151: // EnemyBuildingsInTown
      case 152: // EnemyCapturedRelics
      case 153: // EscrowAmount
      case 154: // EventDetected
      case 155: // Falseval
      case 156: // FoodAmount
      case 157: // GameTime
      case 159: // Goal
      case 160: // GoldAmount
      case 161: // HousingHeadroom
      case 162: // IdleFarmCount
      case 165: // MapSize
      case 172: // MapType
      case 189: // MilitaryPopulation
      case 190: // PlayerComputer
      case 191: // PlayerHuman
      case 192: // PlayerInGame
      case 193: // PlayerNumber
      case 211: // PlayerResigned
      case 212: // PlayersBuildingCount
      case 213: // PlayersBuildingTypeCount
      case 214: // PlayersCiv
      case 215: // PlayersCivilianPopulation
      case 216: // PlayersCurrentAge
      case 217: // PlayersCurrentAgeTime
      case 218: // PlayersMilitaryPopulation
      case 219: // PlayersPopulation
      case 220: // PlayersScore
      case 221: // PlayersStance
      case 222: // PlayersTribute
      case 223: // PlayersTributeMemory
      case 224: // PlayersUnitCount
      case 225: // PlayersUnitTypeCount
      case 226: // PlayerValid
      case 227: // Population
      case 228: // PopulationCap
      case 229: // PopulationHeadroom
      case 230: // RandomNumber
      case 231: // RegicideGame
      case 240: // ResearchAvailable
      case 241: // ResearchCompleted
      case 360: // ResourceFound
      case 370: // SharedGoal
      case 371: // SheepAndForageTooFar
      case 372: // SoldierCount
      case 374: // StanceToward
      case 375: // StartingAge
      case 376: // StartingResources
      case 380: // StoneAmount
      case 381: // StrategicNumber
      case 515: // TauntDetected
      case 517: // TimerTriggered
      case 518: // TownUnderAttack
      case 521: // Trueval
      case 654: // UnitAvailable
      case 655: // UnitCount
      case 656: // UnitCountTotal
      case 657: // UnitTypeCount
      case 658: // UnitTypeCountTotal
      case 659: // VictoryCondition
      case 665: // WallCompletedPercentage
      case 666: // WallInvisiblePercentage
      case 671: // WarboatCount
      case 672: // WoodAmount
        value.copy< Fact > (that.value);
        break;

      case 689: // mapsizetype
        value.copy< MapSizeType > (that.value);
        break;

      case 690: // maptypename
        value.copy< MapTypeName > (that.value);
        break;

      case 691: // playernumbertype
        value.copy< PlayerNumberType > (that.value);
        break;

      case 692: // relop
        value.copy< RelOp > (that.value);
        break;

      case 693: // researchitem
        value.copy< ResearchItem > (that.value);
        break;

      case 694: // startingresourcestype
        value.copy< StartingResourcesType > (that.value);
        break;

      case 695: // strategicnumbername
        value.copy< StrategicNumberName > (that.value);
        break;

      case 696: // unit
        value.copy< Unit > (that.value);
        break;

      case 697: // victoryconditionname
        value.copy< VictoryConditionName > (that.value);
        break;

      case 698: // walltype
        value.copy< WallType > (that.value);
        break;

      case 3: // Number
        value.copy< int > (that.value);
        break;

      case 681: // singleaction
      case 699: // acknowledgeevent
      case 700: // acknowledgetaunt
      case 701: // attacknow
      case 702: // build
      case 703: // buildforward
      case 704: // buildgate
      case 705: // buildwall
      case 706: // buycommodity
      case 707: // ccaddresource
      case 708: // chatlocal
      case 709: // chatlocaltoself
      case 710: // chatlocalusingid
      case 711: // chatlocalusingrange
      case 712: // chattoall
      case 713: // chattoallusingid
      case 714: // chattoallusingrange
      case 715: // chattoallies
      case 716: // chattoalliesusingid
      case 717: // chattoalliesusingrange
      case 718: // chattoenemies
      case 719: // chattoenemiesusingid
      case 720: // chattoenemiesusingrange
      case 721: // chattoplayer
      case 722: // chattoplayerusingid
      case 723: // chattoplayerusingrange
      case 724: // chattrace
      case 725: // cleartributememory
      case 726: // deletebuilding
      case 727: // deleteunit
      case 728: // disableself
      case 729: // disabletimer
      case 730: // donothing
      case 731: // enabletimer
      case 732: // enablewallplacement
      case 733: // generaterandomnumber
      case 734: // log
      case 735: // logtrace
      case 736: // releaseescrow
      case 737: // research
      case 738: // resign
      case 739: // sellcommodity
      case 740: // setdifficultyparameter
      case 741: // setdoctrine
      case 742: // setescrowpercentage
      case 743: // setgoal
      case 744: // setsharedgoal
      case 745: // setsignal
      case 746: // setstance
      case 747: // setstrategicnumber
      case 748: // spy
      case 749: // taunt
      case 750: // tauntusingrange
      case 751: // train
      case 752: // tributetoplayer
      case 753: // action
        value.copy< std::shared_ptr<ai::Action> > (that.value);
        break;

      case 676: // rule
        value.copy< std::shared_ptr<ai::AiRule> > (that.value);
        break;

      case 678: // condition
      case 679: // conditiontype
      case 754: // trueval
      case 755: // falseval
      case 756: // attacksoldiercount
      case 757: // attackwarboatcount
      case 758: // buildingavailable
      case 759: // buildingcount
      case 760: // buildingcounttotal
      case 761: // buildingtypecount
      case 762: // buildingtypecounttotal
      case 763: // canaffordbuilding
      case 764: // canaffordcompletewall
      case 765: // canaffordresearch
      case 766: // canaffordunit
      case 767: // canbuild
      case 768: // canbuildgate
      case 769: // canbuildgatewithescrow
      case 770: // canbuildwall
      case 771: // canbuildwallwithescrow
      case 772: // canbuildwithescrow
      case 773: // canbuycommodity
      case 774: // canresearch
      case 775: // canresearchwithescrow
      case 776: // cansellcommodity
      case 777: // canspy
      case 778: // canspywithescrow
      case 779: // cantrain
      case 780: // cantrainwithescrow
      case 781: // ccplayersbuildingcount
      case 782: // ccplayersbuildingtypecount
      case 783: // ccplayersunitcount
      case 784: // ccplayersunittypecount
      case 785: // cheatsenabled
      case 786: // civselected
      case 787: // civilianpopulation
      case 788: // commoditybuyingprice
      case 789: // commoditysellingprice
      case 790: // currentage
      case 791: // currentagetime
      case 792: // currentscore
      case 793: // deathmatchgame
      case 794: // defendsoldiercount
      case 795: // defendwarboatcount
      case 796: // difficulty
      case 797: // doctrine
      case 798: // dropsitemindistance
      case 799: // enemybuildingsintown
      case 800: // enemycapturedrelics
      case 801: // escrowamount
      case 802: // eventdetected
      case 803: // foodamount
      case 804: // gametime
      case 805: // goal
      case 806: // goldamount
      case 807: // housingheadroom
      case 808: // idlefarmcount
      case 809: // mapsize
      case 810: // maptype
      case 811: // militarypopulation
      case 812: // playercomputer
      case 813: // playerhuman
      case 814: // playeringame
      case 815: // playernumber
      case 816: // playerresigned
      case 817: // playervalid
      case 818: // playersbuildingcount
      case 819: // playersbuildingtypecount
      case 820: // playersciv
      case 821: // playerscivilianpopulation
      case 822: // playerscurrentage
      case 823: // playerscurrentagetime
      case 824: // playersmilitarypopulation
      case 825: // playerspopulation
      case 826: // playersscore
      case 827: // playersstance
      case 828: // playerstribute
      case 829: // playerstributememory
      case 830: // playersunitcount
      case 831: // playersunittypecount
      case 832: // population
      case 833: // populationcap
      case 834: // populationheadroom
      case 835: // randomnumber
      case 836: // regicidegame
      case 837: // researchavailable
      case 838: // researchcompleted
      case 839: // resourcefound
      case 840: // sharedgoal
      case 841: // sheepandforagetoofar
      case 842: // soldiercount
      case 843: // stancetoward
      case 844: // startingage
      case 845: // startingresources
      case 846: // stoneamount
      case 847: // strategicnumber
      case 848: // tauntdetected
      case 849: // timertriggered
      case 850: // townunderattack
      case 851: // unitavailable
      case 852: // unitcount
      case 853: // unitcounttotal
      case 854: // unittypecount
      case 855: // unittypecounttotal
      case 856: // victorycondition
      case 857: // wallcompletedpercentage
      case 858: // wallinvisiblepercentage
      case 859: // warboatcount
      case 860: // woodamount
      case 861: // fact
        value.copy< std::shared_ptr<ai::Condition> > (that.value);
        break;

      case 4: // String
      case 5: // SymbolName
        value.copy< std::string > (that.value);
        break;

      case 680: // actions
        value.copy< std::vector<std::shared_ptr<ai::Action>> > (that.value);
        break;

      case 677: // conditions
        value.copy< std::vector<std::shared_ptr<ai::Condition>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  ScriptParser::stack_symbol_type&
  ScriptParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 17: // AcknowledgeEvent
      case 18: // AcknowledgeTaunt
      case 24: // AttackNow
      case 27: // Build
      case 28: // BuildForward
      case 29: // BuildGate
      case 59: // BuildWall
      case 60: // BuyCommodity
      case 79: // CcAddResource
      case 84: // ChatLocal
      case 85: // ChatLocalToSelf
      case 86: // ChatLocalUsingId
      case 87: // ChatLocalUsingRange
      case 88: // ChatToAll
      case 89: // ChatToAllies
      case 90: // ChatToAlliesUsingId
      case 91: // ChatToAlliesUsingRange
      case 92: // ChatToAllUsingId
      case 93: // ChatToAllUsingRange
      case 94: // ChatToEnemies
      case 95: // ChatToEnemiesUsingId
      case 96: // ChatToEnemiesUsingRange
      case 97: // ChatToPlayer
      case 98: // ChatToPlayerUsingId
      case 99: // ChatToPlayerUsingRange
      case 100: // ChatTrace
      case 118: // ClearTributeMemory
      case 131: // DeleteBuilding
      case 132: // DeleteUnit
      case 144: // DisableSelf
      case 145: // DisableTimer
      case 147: // DoNothing
      case 149: // EnableTimer
      case 150: // EnableWallPlacement
      case 158: // GenerateRandomNumber
      case 163: // Log
      case 164: // LogTrace
      case 232: // ReleaseEscrow
      case 239: // Research
      case 359: // Resign
      case 361: // SellCommodity
      case 362: // SetDifficultyParameter
      case 363: // SetDoctrine
      case 364: // SetEscrowPercentage
      case 365: // SetGoal
      case 366: // SetSharedGoal
      case 367: // SetSignal
      case 368: // SetStance
      case 369: // SetStrategicNumber
      case 373: // Spy
      case 514: // Taunt
      case 516: // TauntUsingRange
      case 519: // Train
      case 520: // TributeToPlayer
        value.move< ActionType > (that.value);
        break;

      case 682: // age
        value.move< Age > (that.value);
        break;

      case 683: // building
        value.move< Building > (that.value);
        break;

      case 684: // civ
        value.move< Civ > (that.value);
        break;

      case 685: // commodity
        value.move< Commodity > (that.value);
        break;

      case 686: // difficultylevel
        value.move< DifficultyLevel > (that.value);
        break;

      case 687: // difficultyparameter
        value.move< DifficultyParameter > (that.value);
        break;

      case 688: // diplomaticstance
        value.move< DiplomaticStance > (that.value);
        break;

      case 25: // AttackSoldierCount
      case 26: // AttackWarboatCount
      case 54: // BuildingAvailable
      case 55: // BuildingCount
      case 56: // BuildingCountTotal
      case 57: // BuildingTypeCount
      case 58: // BuildingTypeCountTotal
      case 61: // CanAffordBuilding
      case 62: // CanAffordCompleteWall
      case 63: // CanAffordResearch
      case 64: // CanAffordUnit
      case 65: // CanBuild
      case 66: // CanBuildGate
      case 67: // CanBuildGateWithEscrow
      case 68: // CanBuildWall
      case 69: // CanBuildWallWithEscrow
      case 70: // CanBuildWithEscrow
      case 71: // CanBuyCommodity
      case 72: // CanResearch
      case 73: // CanResearchWithEscrow
      case 74: // CanSellCommodity
      case 75: // CanSpy
      case 76: // CanSpyWithEscrow
      case 77: // CanTrain
      case 78: // CanTrainWithEscrow
      case 80: // CcPlayersBuildingCount
      case 81: // CcPlayersBuildingTypeCount
      case 82: // CcPlayersUnitCount
      case 83: // CcPlayersUnitTypeCount
      case 101: // CheatsEnabled
      case 116: // CivilianPopulation
      case 117: // CivSelected
      case 119: // CommodityBuyingPrice
      case 124: // CommoditySellingPrice
      case 125: // CurrentAge
      case 126: // CurrentAgeTime
      case 127: // CurrentScore
      case 128: // DeathMatchGame
      case 129: // DefendSoldierCount
      case 130: // DefendWarboatCount
      case 133: // Difficulty
      case 146: // Doctrine
      case 148: // DropsiteMinDistance
      case 151: // EnemyBuildingsInTown
      case 152: // EnemyCapturedRelics
      case 153: // EscrowAmount
      case 154: // EventDetected
      case 155: // Falseval
      case 156: // FoodAmount
      case 157: // GameTime
      case 159: // Goal
      case 160: // GoldAmount
      case 161: // HousingHeadroom
      case 162: // IdleFarmCount
      case 165: // MapSize
      case 172: // MapType
      case 189: // MilitaryPopulation
      case 190: // PlayerComputer
      case 191: // PlayerHuman
      case 192: // PlayerInGame
      case 193: // PlayerNumber
      case 211: // PlayerResigned
      case 212: // PlayersBuildingCount
      case 213: // PlayersBuildingTypeCount
      case 214: // PlayersCiv
      case 215: // PlayersCivilianPopulation
      case 216: // PlayersCurrentAge
      case 217: // PlayersCurrentAgeTime
      case 218: // PlayersMilitaryPopulation
      case 219: // PlayersPopulation
      case 220: // PlayersScore
      case 221: // PlayersStance
      case 222: // PlayersTribute
      case 223: // PlayersTributeMemory
      case 224: // PlayersUnitCount
      case 225: // PlayersUnitTypeCount
      case 226: // PlayerValid
      case 227: // Population
      case 228: // PopulationCap
      case 229: // PopulationHeadroom
      case 230: // RandomNumber
      case 231: // RegicideGame
      case 240: // ResearchAvailable
      case 241: // ResearchCompleted
      case 360: // ResourceFound
      case 370: // SharedGoal
      case 371: // SheepAndForageTooFar
      case 372: // SoldierCount
      case 374: // StanceToward
      case 375: // StartingAge
      case 376: // StartingResources
      case 380: // StoneAmount
      case 381: // StrategicNumber
      case 515: // TauntDetected
      case 517: // TimerTriggered
      case 518: // TownUnderAttack
      case 521: // Trueval
      case 654: // UnitAvailable
      case 655: // UnitCount
      case 656: // UnitCountTotal
      case 657: // UnitTypeCount
      case 658: // UnitTypeCountTotal
      case 659: // VictoryCondition
      case 665: // WallCompletedPercentage
      case 666: // WallInvisiblePercentage
      case 671: // WarboatCount
      case 672: // WoodAmount
        value.move< Fact > (that.value);
        break;

      case 689: // mapsizetype
        value.move< MapSizeType > (that.value);
        break;

      case 690: // maptypename
        value.move< MapTypeName > (that.value);
        break;

      case 691: // playernumbertype
        value.move< PlayerNumberType > (that.value);
        break;

      case 692: // relop
        value.move< RelOp > (that.value);
        break;

      case 693: // researchitem
        value.move< ResearchItem > (that.value);
        break;

      case 694: // startingresourcestype
        value.move< StartingResourcesType > (that.value);
        break;

      case 695: // strategicnumbername
        value.move< StrategicNumberName > (that.value);
        break;

      case 696: // unit
        value.move< Unit > (that.value);
        break;

      case 697: // victoryconditionname
        value.move< VictoryConditionName > (that.value);
        break;

      case 698: // walltype
        value.move< WallType > (that.value);
        break;

      case 3: // Number
        value.move< int > (that.value);
        break;

      case 681: // singleaction
      case 699: // acknowledgeevent
      case 700: // acknowledgetaunt
      case 701: // attacknow
      case 702: // build
      case 703: // buildforward
      case 704: // buildgate
      case 705: // buildwall
      case 706: // buycommodity
      case 707: // ccaddresource
      case 708: // chatlocal
      case 709: // chatlocaltoself
      case 710: // chatlocalusingid
      case 711: // chatlocalusingrange
      case 712: // chattoall
      case 713: // chattoallusingid
      case 714: // chattoallusingrange
      case 715: // chattoallies
      case 716: // chattoalliesusingid
      case 717: // chattoalliesusingrange
      case 718: // chattoenemies
      case 719: // chattoenemiesusingid
      case 720: // chattoenemiesusingrange
      case 721: // chattoplayer
      case 722: // chattoplayerusingid
      case 723: // chattoplayerusingrange
      case 724: // chattrace
      case 725: // cleartributememory
      case 726: // deletebuilding
      case 727: // deleteunit
      case 728: // disableself
      case 729: // disabletimer
      case 730: // donothing
      case 731: // enabletimer
      case 732: // enablewallplacement
      case 733: // generaterandomnumber
      case 734: // log
      case 735: // logtrace
      case 736: // releaseescrow
      case 737: // research
      case 738: // resign
      case 739: // sellcommodity
      case 740: // setdifficultyparameter
      case 741: // setdoctrine
      case 742: // setescrowpercentage
      case 743: // setgoal
      case 744: // setsharedgoal
      case 745: // setsignal
      case 746: // setstance
      case 747: // setstrategicnumber
      case 748: // spy
      case 749: // taunt
      case 750: // tauntusingrange
      case 751: // train
      case 752: // tributetoplayer
      case 753: // action
        value.move< std::shared_ptr<ai::Action> > (that.value);
        break;

      case 676: // rule
        value.move< std::shared_ptr<ai::AiRule> > (that.value);
        break;

      case 678: // condition
      case 679: // conditiontype
      case 754: // trueval
      case 755: // falseval
      case 756: // attacksoldiercount
      case 757: // attackwarboatcount
      case 758: // buildingavailable
      case 759: // buildingcount
      case 760: // buildingcounttotal
      case 761: // buildingtypecount
      case 762: // buildingtypecounttotal
      case 763: // canaffordbuilding
      case 764: // canaffordcompletewall
      case 765: // canaffordresearch
      case 766: // canaffordunit
      case 767: // canbuild
      case 768: // canbuildgate
      case 769: // canbuildgatewithescrow
      case 770: // canbuildwall
      case 771: // canbuildwallwithescrow
      case 772: // canbuildwithescrow
      case 773: // canbuycommodity
      case 774: // canresearch
      case 775: // canresearchwithescrow
      case 776: // cansellcommodity
      case 777: // canspy
      case 778: // canspywithescrow
      case 779: // cantrain
      case 780: // cantrainwithescrow
      case 781: // ccplayersbuildingcount
      case 782: // ccplayersbuildingtypecount
      case 783: // ccplayersunitcount
      case 784: // ccplayersunittypecount
      case 785: // cheatsenabled
      case 786: // civselected
      case 787: // civilianpopulation
      case 788: // commoditybuyingprice
      case 789: // commoditysellingprice
      case 790: // currentage
      case 791: // currentagetime
      case 792: // currentscore
      case 793: // deathmatchgame
      case 794: // defendsoldiercount
      case 795: // defendwarboatcount
      case 796: // difficulty
      case 797: // doctrine
      case 798: // dropsitemindistance
      case 799: // enemybuildingsintown
      case 800: // enemycapturedrelics
      case 801: // escrowamount
      case 802: // eventdetected
      case 803: // foodamount
      case 804: // gametime
      case 805: // goal
      case 806: // goldamount
      case 807: // housingheadroom
      case 808: // idlefarmcount
      case 809: // mapsize
      case 810: // maptype
      case 811: // militarypopulation
      case 812: // playercomputer
      case 813: // playerhuman
      case 814: // playeringame
      case 815: // playernumber
      case 816: // playerresigned
      case 817: // playervalid
      case 818: // playersbuildingcount
      case 819: // playersbuildingtypecount
      case 820: // playersciv
      case 821: // playerscivilianpopulation
      case 822: // playerscurrentage
      case 823: // playerscurrentagetime
      case 824: // playersmilitarypopulation
      case 825: // playerspopulation
      case 826: // playersscore
      case 827: // playersstance
      case 828: // playerstribute
      case 829: // playerstributememory
      case 830: // playersunitcount
      case 831: // playersunittypecount
      case 832: // population
      case 833: // populationcap
      case 834: // populationheadroom
      case 835: // randomnumber
      case 836: // regicidegame
      case 837: // researchavailable
      case 838: // researchcompleted
      case 839: // resourcefound
      case 840: // sharedgoal
      case 841: // sheepandforagetoofar
      case 842: // soldiercount
      case 843: // stancetoward
      case 844: // startingage
      case 845: // startingresources
      case 846: // stoneamount
      case 847: // strategicnumber
      case 848: // tauntdetected
      case 849: // timertriggered
      case 850: // townunderattack
      case 851: // unitavailable
      case 852: // unitcount
      case 853: // unitcounttotal
      case 854: // unittypecount
      case 855: // unittypecounttotal
      case 856: // victorycondition
      case 857: // wallcompletedpercentage
      case 858: // wallinvisiblepercentage
      case 859: // warboatcount
      case 860: // woodamount
      case 861: // fact
        value.move< std::shared_ptr<ai::Condition> > (that.value);
        break;

      case 4: // String
      case 5: // SymbolName
        value.move< std::string > (that.value);
        break;

      case 680: // actions
        value.move< std::vector<std::shared_ptr<ai::Action>> > (that.value);
        break;

      case 677: // conditions
        value.move< std::vector<std::shared_ptr<ai::Condition>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  ScriptParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  ScriptParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  ScriptParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  ScriptParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  ScriptParser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  ScriptParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ScriptParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ScriptParser::debug_level_type
  ScriptParser::debug_level () const
  {
    return yydebug_;
  }

  void
  ScriptParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  ScriptParser::state_type
  ScriptParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  ScriptParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  ScriptParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  ScriptParser::operator() ()
  {
    return parse ();
  }

  int
  ScriptParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 17: // AcknowledgeEvent
      case 18: // AcknowledgeTaunt
      case 24: // AttackNow
      case 27: // Build
      case 28: // BuildForward
      case 29: // BuildGate
      case 59: // BuildWall
      case 60: // BuyCommodity
      case 79: // CcAddResource
      case 84: // ChatLocal
      case 85: // ChatLocalToSelf
      case 86: // ChatLocalUsingId
      case 87: // ChatLocalUsingRange
      case 88: // ChatToAll
      case 89: // ChatToAllies
      case 90: // ChatToAlliesUsingId
      case 91: // ChatToAlliesUsingRange
      case 92: // ChatToAllUsingId
      case 93: // ChatToAllUsingRange
      case 94: // ChatToEnemies
      case 95: // ChatToEnemiesUsingId
      case 96: // ChatToEnemiesUsingRange
      case 97: // ChatToPlayer
      case 98: // ChatToPlayerUsingId
      case 99: // ChatToPlayerUsingRange
      case 100: // ChatTrace
      case 118: // ClearTributeMemory
      case 131: // DeleteBuilding
      case 132: // DeleteUnit
      case 144: // DisableSelf
      case 145: // DisableTimer
      case 147: // DoNothing
      case 149: // EnableTimer
      case 150: // EnableWallPlacement
      case 158: // GenerateRandomNumber
      case 163: // Log
      case 164: // LogTrace
      case 232: // ReleaseEscrow
      case 239: // Research
      case 359: // Resign
      case 361: // SellCommodity
      case 362: // SetDifficultyParameter
      case 363: // SetDoctrine
      case 364: // SetEscrowPercentage
      case 365: // SetGoal
      case 366: // SetSharedGoal
      case 367: // SetSignal
      case 368: // SetStance
      case 369: // SetStrategicNumber
      case 373: // Spy
      case 514: // Taunt
      case 516: // TauntUsingRange
      case 519: // Train
      case 520: // TributeToPlayer
        yylhs.value.emplace< ActionType > ();
        break;

      case 682: // age
        yylhs.value.emplace< Age > ();
        break;

      case 683: // building
        yylhs.value.emplace< Building > ();
        break;

      case 684: // civ
        yylhs.value.emplace< Civ > ();
        break;

      case 685: // commodity
        yylhs.value.emplace< Commodity > ();
        break;

      case 686: // difficultylevel
        yylhs.value.emplace< DifficultyLevel > ();
        break;

      case 687: // difficultyparameter
        yylhs.value.emplace< DifficultyParameter > ();
        break;

      case 688: // diplomaticstance
        yylhs.value.emplace< DiplomaticStance > ();
        break;

      case 25: // AttackSoldierCount
      case 26: // AttackWarboatCount
      case 54: // BuildingAvailable
      case 55: // BuildingCount
      case 56: // BuildingCountTotal
      case 57: // BuildingTypeCount
      case 58: // BuildingTypeCountTotal
      case 61: // CanAffordBuilding
      case 62: // CanAffordCompleteWall
      case 63: // CanAffordResearch
      case 64: // CanAffordUnit
      case 65: // CanBuild
      case 66: // CanBuildGate
      case 67: // CanBuildGateWithEscrow
      case 68: // CanBuildWall
      case 69: // CanBuildWallWithEscrow
      case 70: // CanBuildWithEscrow
      case 71: // CanBuyCommodity
      case 72: // CanResearch
      case 73: // CanResearchWithEscrow
      case 74: // CanSellCommodity
      case 75: // CanSpy
      case 76: // CanSpyWithEscrow
      case 77: // CanTrain
      case 78: // CanTrainWithEscrow
      case 80: // CcPlayersBuildingCount
      case 81: // CcPlayersBuildingTypeCount
      case 82: // CcPlayersUnitCount
      case 83: // CcPlayersUnitTypeCount
      case 101: // CheatsEnabled
      case 116: // CivilianPopulation
      case 117: // CivSelected
      case 119: // CommodityBuyingPrice
      case 124: // CommoditySellingPrice
      case 125: // CurrentAge
      case 126: // CurrentAgeTime
      case 127: // CurrentScore
      case 128: // DeathMatchGame
      case 129: // DefendSoldierCount
      case 130: // DefendWarboatCount
      case 133: // Difficulty
      case 146: // Doctrine
      case 148: // DropsiteMinDistance
      case 151: // EnemyBuildingsInTown
      case 152: // EnemyCapturedRelics
      case 153: // EscrowAmount
      case 154: // EventDetected
      case 155: // Falseval
      case 156: // FoodAmount
      case 157: // GameTime
      case 159: // Goal
      case 160: // GoldAmount
      case 161: // HousingHeadroom
      case 162: // IdleFarmCount
      case 165: // MapSize
      case 172: // MapType
      case 189: // MilitaryPopulation
      case 190: // PlayerComputer
      case 191: // PlayerHuman
      case 192: // PlayerInGame
      case 193: // PlayerNumber
      case 211: // PlayerResigned
      case 212: // PlayersBuildingCount
      case 213: // PlayersBuildingTypeCount
      case 214: // PlayersCiv
      case 215: // PlayersCivilianPopulation
      case 216: // PlayersCurrentAge
      case 217: // PlayersCurrentAgeTime
      case 218: // PlayersMilitaryPopulation
      case 219: // PlayersPopulation
      case 220: // PlayersScore
      case 221: // PlayersStance
      case 222: // PlayersTribute
      case 223: // PlayersTributeMemory
      case 224: // PlayersUnitCount
      case 225: // PlayersUnitTypeCount
      case 226: // PlayerValid
      case 227: // Population
      case 228: // PopulationCap
      case 229: // PopulationHeadroom
      case 230: // RandomNumber
      case 231: // RegicideGame
      case 240: // ResearchAvailable
      case 241: // ResearchCompleted
      case 360: // ResourceFound
      case 370: // SharedGoal
      case 371: // SheepAndForageTooFar
      case 372: // SoldierCount
      case 374: // StanceToward
      case 375: // StartingAge
      case 376: // StartingResources
      case 380: // StoneAmount
      case 381: // StrategicNumber
      case 515: // TauntDetected
      case 517: // TimerTriggered
      case 518: // TownUnderAttack
      case 521: // Trueval
      case 654: // UnitAvailable
      case 655: // UnitCount
      case 656: // UnitCountTotal
      case 657: // UnitTypeCount
      case 658: // UnitTypeCountTotal
      case 659: // VictoryCondition
      case 665: // WallCompletedPercentage
      case 666: // WallInvisiblePercentage
      case 671: // WarboatCount
      case 672: // WoodAmount
        yylhs.value.emplace< Fact > ();
        break;

      case 689: // mapsizetype
        yylhs.value.emplace< MapSizeType > ();
        break;

      case 690: // maptypename
        yylhs.value.emplace< MapTypeName > ();
        break;

      case 691: // playernumbertype
        yylhs.value.emplace< PlayerNumberType > ();
        break;

      case 692: // relop
        yylhs.value.emplace< RelOp > ();
        break;

      case 693: // researchitem
        yylhs.value.emplace< ResearchItem > ();
        break;

      case 694: // startingresourcestype
        yylhs.value.emplace< StartingResourcesType > ();
        break;

      case 695: // strategicnumbername
        yylhs.value.emplace< StrategicNumberName > ();
        break;

      case 696: // unit
        yylhs.value.emplace< Unit > ();
        break;

      case 697: // victoryconditionname
        yylhs.value.emplace< VictoryConditionName > ();
        break;

      case 698: // walltype
        yylhs.value.emplace< WallType > ();
        break;

      case 3: // Number
        yylhs.value.emplace< int > ();
        break;

      case 681: // singleaction
      case 699: // acknowledgeevent
      case 700: // acknowledgetaunt
      case 701: // attacknow
      case 702: // build
      case 703: // buildforward
      case 704: // buildgate
      case 705: // buildwall
      case 706: // buycommodity
      case 707: // ccaddresource
      case 708: // chatlocal
      case 709: // chatlocaltoself
      case 710: // chatlocalusingid
      case 711: // chatlocalusingrange
      case 712: // chattoall
      case 713: // chattoallusingid
      case 714: // chattoallusingrange
      case 715: // chattoallies
      case 716: // chattoalliesusingid
      case 717: // chattoalliesusingrange
      case 718: // chattoenemies
      case 719: // chattoenemiesusingid
      case 720: // chattoenemiesusingrange
      case 721: // chattoplayer
      case 722: // chattoplayerusingid
      case 723: // chattoplayerusingrange
      case 724: // chattrace
      case 725: // cleartributememory
      case 726: // deletebuilding
      case 727: // deleteunit
      case 728: // disableself
      case 729: // disabletimer
      case 730: // donothing
      case 731: // enabletimer
      case 732: // enablewallplacement
      case 733: // generaterandomnumber
      case 734: // log
      case 735: // logtrace
      case 736: // releaseescrow
      case 737: // research
      case 738: // resign
      case 739: // sellcommodity
      case 740: // setdifficultyparameter
      case 741: // setdoctrine
      case 742: // setescrowpercentage
      case 743: // setgoal
      case 744: // setsharedgoal
      case 745: // setsignal
      case 746: // setstance
      case 747: // setstrategicnumber
      case 748: // spy
      case 749: // taunt
      case 750: // tauntusingrange
      case 751: // train
      case 752: // tributetoplayer
      case 753: // action
        yylhs.value.emplace< std::shared_ptr<ai::Action> > ();
        break;

      case 676: // rule
        yylhs.value.emplace< std::shared_ptr<ai::AiRule> > ();
        break;

      case 678: // condition
      case 679: // conditiontype
      case 754: // trueval
      case 755: // falseval
      case 756: // attacksoldiercount
      case 757: // attackwarboatcount
      case 758: // buildingavailable
      case 759: // buildingcount
      case 760: // buildingcounttotal
      case 761: // buildingtypecount
      case 762: // buildingtypecounttotal
      case 763: // canaffordbuilding
      case 764: // canaffordcompletewall
      case 765: // canaffordresearch
      case 766: // canaffordunit
      case 767: // canbuild
      case 768: // canbuildgate
      case 769: // canbuildgatewithescrow
      case 770: // canbuildwall
      case 771: // canbuildwallwithescrow
      case 772: // canbuildwithescrow
      case 773: // canbuycommodity
      case 774: // canresearch
      case 775: // canresearchwithescrow
      case 776: // cansellcommodity
      case 777: // canspy
      case 778: // canspywithescrow
      case 779: // cantrain
      case 780: // cantrainwithescrow
      case 781: // ccplayersbuildingcount
      case 782: // ccplayersbuildingtypecount
      case 783: // ccplayersunitcount
      case 784: // ccplayersunittypecount
      case 785: // cheatsenabled
      case 786: // civselected
      case 787: // civilianpopulation
      case 788: // commoditybuyingprice
      case 789: // commoditysellingprice
      case 790: // currentage
      case 791: // currentagetime
      case 792: // currentscore
      case 793: // deathmatchgame
      case 794: // defendsoldiercount
      case 795: // defendwarboatcount
      case 796: // difficulty
      case 797: // doctrine
      case 798: // dropsitemindistance
      case 799: // enemybuildingsintown
      case 800: // enemycapturedrelics
      case 801: // escrowamount
      case 802: // eventdetected
      case 803: // foodamount
      case 804: // gametime
      case 805: // goal
      case 806: // goldamount
      case 807: // housingheadroom
      case 808: // idlefarmcount
      case 809: // mapsize
      case 810: // maptype
      case 811: // militarypopulation
      case 812: // playercomputer
      case 813: // playerhuman
      case 814: // playeringame
      case 815: // playernumber
      case 816: // playerresigned
      case 817: // playervalid
      case 818: // playersbuildingcount
      case 819: // playersbuildingtypecount
      case 820: // playersciv
      case 821: // playerscivilianpopulation
      case 822: // playerscurrentage
      case 823: // playerscurrentagetime
      case 824: // playersmilitarypopulation
      case 825: // playerspopulation
      case 826: // playersscore
      case 827: // playersstance
      case 828: // playerstribute
      case 829: // playerstributememory
      case 830: // playersunitcount
      case 831: // playersunittypecount
      case 832: // population
      case 833: // populationcap
      case 834: // populationheadroom
      case 835: // randomnumber
      case 836: // regicidegame
      case 837: // researchavailable
      case 838: // researchcompleted
      case 839: // resourcefound
      case 840: // sharedgoal
      case 841: // sheepandforagetoofar
      case 842: // soldiercount
      case 843: // stancetoward
      case 844: // startingage
      case 845: // startingresources
      case 846: // stoneamount
      case 847: // strategicnumber
      case 848: // tauntdetected
      case 849: // timertriggered
      case 850: // townunderattack
      case 851: // unitavailable
      case 852: // unitcount
      case 853: // unitcounttotal
      case 854: // unittypecount
      case 855: // unittypecounttotal
      case 856: // victorycondition
      case 857: // wallcompletedpercentage
      case 858: // wallinvisiblepercentage
      case 859: // warboatcount
      case 860: // woodamount
      case 861: // fact
        yylhs.value.emplace< std::shared_ptr<ai::Condition> > ();
        break;

      case 4: // String
      case 5: // SymbolName
        yylhs.value.emplace< std::string > ();
        break;

      case 680: // actions
        yylhs.value.emplace< std::vector<std::shared_ptr<ai::Action>> > ();
        break;

      case 677: // conditions
        yylhs.value.emplace< std::vector<std::shared_ptr<ai::Condition>> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 3:
#line 605 "grammar.gen.ypp"
                      { printf("got script\n"); }
#line 2723 "grammar.gen.tab.cpp"
    break;

  case 4:
#line 609 "grammar.gen.ypp"
         { printf("got single rule\n"); }
#line 2729 "grammar.gen.tab.cpp"
    break;

  case 5:
#line 610 "grammar.gen.ypp"
                 { /*printf("got multiple rules\n");*/ }
#line 2735 "grammar.gen.tab.cpp"
    break;

  case 6:
#line 613 "grammar.gen.ypp"
                                                                               { driver.addRule(yystack_[3].value.as < std::vector<std::shared_ptr<ai::Condition>> > (), yystack_[1].value.as < std::vector<std::shared_ptr<ai::Action>> > ()); }
#line 2741 "grammar.gen.tab.cpp"
    break;

  case 7:
#line 616 "grammar.gen.ypp"
              { std::vector<std::shared_ptr<ai::Condition>> ret; ret.push_back(yystack_[0].value.as < std::shared_ptr<ai::Condition> > ()); yylhs.value.as < std::vector<std::shared_ptr<ai::Condition>> > () = ret; /* printf("got single condition\n");*/ }
#line 2747 "grammar.gen.tab.cpp"
    break;

  case 8:
#line 617 "grammar.gen.ypp"
                           { yystack_[0].value.as < std::vector<std::shared_ptr<ai::Condition>> > ().push_back(yystack_[1].value.as < std::shared_ptr<ai::Condition> > ()); yylhs.value.as < std::vector<std::shared_ptr<ai::Condition>> > () = yystack_[0].value.as < std::vector<std::shared_ptr<ai::Condition>> > (); }
#line 2753 "grammar.gen.tab.cpp"
    break;

  case 9:
#line 620 "grammar.gen.ypp"
                                       { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[1].value.as < std::shared_ptr<ai::Condition> > (); /*printf("condition\n");*/ }
#line 2759 "grammar.gen.tab.cpp"
    break;

  case 10:
#line 623 "grammar.gen.ypp"
                  { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createNotCondition(yystack_[0].value.as < std::shared_ptr<ai::Condition> > ()); /*printf("got negated condition\n");*/ }
#line 2765 "grammar.gen.tab.cpp"
    break;

  case 11:
#line 624 "grammar.gen.ypp"
                             { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createOrCondition(yystack_[1].value.as < std::shared_ptr<ai::Condition> > (), yystack_[0].value.as < std::shared_ptr<ai::Condition> > ()); /*printf("got multiple or conditions\n"); */ }
#line 2771 "grammar.gen.tab.cpp"
    break;

  case 12:
#line 625 "grammar.gen.ypp"
           { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); /*printf("got fact\n"); */ }
#line 2777 "grammar.gen.tab.cpp"
    break;

  case 13:
#line 629 "grammar.gen.ypp"
                 { std::vector<std::shared_ptr<ai::Action>> ret; ret.push_back(yystack_[0].value.as < std::shared_ptr<ai::Action> > ()); yylhs.value.as < std::vector<std::shared_ptr<ai::Action>> > () = ret; /*printf("got single action\n");*/ }
#line 2783 "grammar.gen.tab.cpp"
    break;

  case 14:
#line 630 "grammar.gen.ypp"
                           { yystack_[0].value.as < std::vector<std::shared_ptr<ai::Action>> > ().push_back(yystack_[1].value.as < std::shared_ptr<ai::Action> > ()); yylhs.value.as < std::vector<std::shared_ptr<ai::Action>> > () = yystack_[0].value.as < std::vector<std::shared_ptr<ai::Action>> > (); /*printf("got multiple actions\n");*/ }
#line 2789 "grammar.gen.tab.cpp"
    break;

  case 15:
#line 633 "grammar.gen.ypp"
                                  { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[1].value.as < std::shared_ptr<ai::Action> > (); /*printf("got action without arguments\n");*/ }
#line 2795 "grammar.gen.tab.cpp"
    break;

  case 16:
#line 636 "grammar.gen.ypp"
                { yylhs.value.as < Age > () = Age::DarkAge; }
#line 2801 "grammar.gen.tab.cpp"
    break;

  case 17:
#line 637 "grammar.gen.ypp"
                  { yylhs.value.as < Age > () = Age::FeudalAge; }
#line 2807 "grammar.gen.tab.cpp"
    break;

  case 18:
#line 638 "grammar.gen.ypp"
                  { yylhs.value.as < Age > () = Age::CastleAge; }
#line 2813 "grammar.gen.tab.cpp"
    break;

  case 19:
#line 639 "grammar.gen.ypp"
                    { yylhs.value.as < Age > () = Age::ImperialAge; }
#line 2819 "grammar.gen.tab.cpp"
    break;

  case 20:
#line 640 "grammar.gen.ypp"
                        { yylhs.value.as < Age > () = Age::PostImperialAge; }
#line 2825 "grammar.gen.tab.cpp"
    break;

  case 21:
#line 641 "grammar.gen.ypp"
                     { yylhs.value.as < Age > () = Age::CastleAge; }
#line 2831 "grammar.gen.tab.cpp"
    break;

  case 22:
#line 644 "grammar.gen.ypp"
                          { yylhs.value.as < Building > () = Building::ArcheryRange; }
#line 2837 "grammar.gen.tab.cpp"
    break;

  case 23:
#line 645 "grammar.gen.ypp"
                      { yylhs.value.as < Building > () = Building::Barracks; }
#line 2843 "grammar.gen.tab.cpp"
    break;

  case 24:
#line 646 "grammar.gen.ypp"
                        { yylhs.value.as < Building > () = Building::Blacksmith; }
#line 2849 "grammar.gen.tab.cpp"
    break;

  case 25:
#line 647 "grammar.gen.ypp"
                          { yylhs.value.as < Building > () = Building::BombardTower; }
#line 2855 "grammar.gen.tab.cpp"
    break;

  case 26:
#line 648 "grammar.gen.ypp"
                    { yylhs.value.as < Building > () = Building::Castle; }
#line 2861 "grammar.gen.tab.cpp"
    break;

  case 27:
#line 649 "grammar.gen.ypp"
                  { yylhs.value.as < Building > () = Building::Dock; }
#line 2867 "grammar.gen.tab.cpp"
    break;

  case 28:
#line 650 "grammar.gen.ypp"
                  { yylhs.value.as < Building > () = Building::Farm; }
#line 2873 "grammar.gen.tab.cpp"
    break;

  case 29:
#line 651 "grammar.gen.ypp"
                      { yylhs.value.as < Building > () = Building::FishTrap; }
#line 2879 "grammar.gen.tab.cpp"
    break;

  case 30:
#line 652 "grammar.gen.ypp"
                        { yylhs.value.as < Building > () = Building::GuardTower; }
#line 2885 "grammar.gen.tab.cpp"
    break;

  case 31:
#line 653 "grammar.gen.ypp"
                   { yylhs.value.as < Building > () = Building::House; }
#line 2891 "grammar.gen.tab.cpp"
    break;

  case 32:
#line 654 "grammar.gen.ypp"
                  { yylhs.value.as < Building > () = Building::Keep; }
#line 2897 "grammar.gen.tab.cpp"
    break;

  case 33:
#line 655 "grammar.gen.ypp"
                        { yylhs.value.as < Building > () = Building::LumberCamp; }
#line 2903 "grammar.gen.tab.cpp"
    break;

  case 34:
#line 656 "grammar.gen.ypp"
                    { yylhs.value.as < Building > () = Building::Market; }
#line 2909 "grammar.gen.tab.cpp"
    break;

  case 35:
#line 657 "grammar.gen.ypp"
                  { yylhs.value.as < Building > () = Building::Mill; }
#line 2915 "grammar.gen.tab.cpp"
    break;

  case 36:
#line 658 "grammar.gen.ypp"
                        { yylhs.value.as < Building > () = Building::MiningCamp; }
#line 2921 "grammar.gen.tab.cpp"
    break;

  case 37:
#line 659 "grammar.gen.ypp"
                       { yylhs.value.as < Building > () = Building::Monastery; }
#line 2927 "grammar.gen.tab.cpp"
    break;

  case 38:
#line 660 "grammar.gen.ypp"
                     { yylhs.value.as < Building > () = Building::Outpost; }
#line 2933 "grammar.gen.tab.cpp"
    break;

  case 39:
#line 661 "grammar.gen.ypp"
                           { yylhs.value.as < Building > () = Building::SiegeWorkshop; }
#line 2939 "grammar.gen.tab.cpp"
    break;

  case 40:
#line 662 "grammar.gen.ypp"
                    { yylhs.value.as < Building > () = Building::Stable; }
#line 2945 "grammar.gen.tab.cpp"
    break;

  case 41:
#line 663 "grammar.gen.ypp"
                        { yylhs.value.as < Building > () = Building::TownCenter; }
#line 2951 "grammar.gen.tab.cpp"
    break;

  case 42:
#line 664 "grammar.gen.ypp"
                        { yylhs.value.as < Building > () = Building::University; }
#line 2957 "grammar.gen.tab.cpp"
    break;

  case 43:
#line 665 "grammar.gen.ypp"
                        { yylhs.value.as < Building > () = Building::WatchTower; }
#line 2963 "grammar.gen.tab.cpp"
    break;

  case 44:
#line 666 "grammar.gen.ypp"
                    { yylhs.value.as < Building > () = Building::Wonder; }
#line 2969 "grammar.gen.tab.cpp"
    break;

  case 45:
#line 667 "grammar.gen.ypp"
                            { yylhs.value.as < Building > () = Building::WatchTowerLine; }
#line 2975 "grammar.gen.tab.cpp"
    break;

  case 46:
#line 670 "grammar.gen.ypp"
               { yylhs.value.as < Civ > () = Civ::Briton; }
#line 2981 "grammar.gen.tab.cpp"
    break;

  case 47:
#line 671 "grammar.gen.ypp"
                  { yylhs.value.as < Civ > () = Civ::Byzantine; }
#line 2987 "grammar.gen.tab.cpp"
    break;

  case 48:
#line 672 "grammar.gen.ypp"
               { yylhs.value.as < Civ > () = Civ::Celtic; }
#line 2993 "grammar.gen.tab.cpp"
    break;

  case 49:
#line 673 "grammar.gen.ypp"
                { yylhs.value.as < Civ > () = Civ::Chinese; }
#line 2999 "grammar.gen.tab.cpp"
    break;

  case 50:
#line 674 "grammar.gen.ypp"
                 { yylhs.value.as < Civ > () = Civ::Frankish; }
#line 3005 "grammar.gen.tab.cpp"
    break;

  case 51:
#line 675 "grammar.gen.ypp"
               { yylhs.value.as < Civ > () = Civ::Gothic; }
#line 3011 "grammar.gen.tab.cpp"
    break;

  case 52:
#line 676 "grammar.gen.ypp"
                 { yylhs.value.as < Civ > () = Civ::Japanese; }
#line 3017 "grammar.gen.tab.cpp"
    break;

  case 53:
#line 677 "grammar.gen.ypp"
               { yylhs.value.as < Civ > () = Civ::Mongol; }
#line 3023 "grammar.gen.tab.cpp"
    break;

  case 54:
#line 678 "grammar.gen.ypp"
                { yylhs.value.as < Civ > () = Civ::Persian; }
#line 3029 "grammar.gen.tab.cpp"
    break;

  case 55:
#line 679 "grammar.gen.ypp"
                { yylhs.value.as < Civ > () = Civ::Saracen; }
#line 3035 "grammar.gen.tab.cpp"
    break;

  case 56:
#line 680 "grammar.gen.ypp"
                 { yylhs.value.as < Civ > () = Civ::Teutonic; }
#line 3041 "grammar.gen.tab.cpp"
    break;

  case 57:
#line 681 "grammar.gen.ypp"
                { yylhs.value.as < Civ > () = Civ::Turkish; }
#line 3047 "grammar.gen.tab.cpp"
    break;

  case 58:
#line 682 "grammar.gen.ypp"
               { yylhs.value.as < Civ > () = Civ::Viking; }
#line 3053 "grammar.gen.tab.cpp"
    break;

  case 59:
#line 683 "grammar.gen.ypp"
              { yylhs.value.as < Civ > () = Civ::MyCiv; }
#line 3059 "grammar.gen.tab.cpp"
    break;

  case 60:
#line 686 "grammar.gen.ypp"
                   { yylhs.value.as < Commodity > () = Commodity::Food; }
#line 3065 "grammar.gen.tab.cpp"
    break;

  case 61:
#line 687 "grammar.gen.ypp"
                    { yylhs.value.as < Commodity > () = Commodity::Stone; }
#line 3071 "grammar.gen.tab.cpp"
    break;

  case 62:
#line 688 "grammar.gen.ypp"
                   { yylhs.value.as < Commodity > () = Commodity::Wood; }
#line 3077 "grammar.gen.tab.cpp"
    break;

  case 63:
#line 689 "grammar.gen.ypp"
                   { yylhs.value.as < Commodity > () = Commodity::Gold; }
#line 3083 "grammar.gen.tab.cpp"
    break;

  case 64:
#line 692 "grammar.gen.ypp"
                            { yylhs.value.as < DifficultyLevel > () = DifficultyLevel::Easiest; }
#line 3089 "grammar.gen.tab.cpp"
    break;

  case 65:
#line 693 "grammar.gen.ypp"
                         { yylhs.value.as < DifficultyLevel > () = DifficultyLevel::Easy; }
#line 3095 "grammar.gen.tab.cpp"
    break;

  case 66:
#line 694 "grammar.gen.ypp"
                             { yylhs.value.as < DifficultyLevel > () = DifficultyLevel::Moderate; }
#line 3101 "grammar.gen.tab.cpp"
    break;

  case 67:
#line 695 "grammar.gen.ypp"
                         { yylhs.value.as < DifficultyLevel > () = DifficultyLevel::Hard; }
#line 3107 "grammar.gen.tab.cpp"
    break;

  case 68:
#line 696 "grammar.gen.ypp"
                            { yylhs.value.as < DifficultyLevel > () = DifficultyLevel::Hardest; }
#line 3113 "grammar.gen.tab.cpp"
    break;

  case 69:
#line 699 "grammar.gen.ypp"
                                               { yylhs.value.as < DifficultyParameter > () = DifficultyParameter::AbilityToDodgeMissiles; }
#line 3119 "grammar.gen.tab.cpp"
    break;

  case 70:
#line 700 "grammar.gen.ypp"
                                                  { yylhs.value.as < DifficultyParameter > () = DifficultyParameter::AbilityToMaintainDistance; }
#line 3125 "grammar.gen.tab.cpp"
    break;

  case 71:
#line 703 "grammar.gen.ypp"
                          { yylhs.value.as < DiplomaticStance > () = DiplomaticStance::Ally; }
#line 3131 "grammar.gen.tab.cpp"
    break;

  case 72:
#line 704 "grammar.gen.ypp"
                             { yylhs.value.as < DiplomaticStance > () = DiplomaticStance::Neutral; }
#line 3137 "grammar.gen.tab.cpp"
    break;

  case 73:
#line 705 "grammar.gen.ypp"
                           { yylhs.value.as < DiplomaticStance > () = DiplomaticStance::Enemy; }
#line 3143 "grammar.gen.tab.cpp"
    break;

  case 74:
#line 708 "grammar.gen.ypp"
                     { yylhs.value.as < MapSizeType > () = MapSizeType::Tiny; }
#line 3149 "grammar.gen.tab.cpp"
    break;

  case 75:
#line 709 "grammar.gen.ypp"
                      { yylhs.value.as < MapSizeType > () = MapSizeType::Small; }
#line 3155 "grammar.gen.tab.cpp"
    break;

  case 76:
#line 710 "grammar.gen.ypp"
                       { yylhs.value.as < MapSizeType > () = MapSizeType::Medium; }
#line 3161 "grammar.gen.tab.cpp"
    break;

  case 77:
#line 711 "grammar.gen.ypp"
                       { yylhs.value.as < MapSizeType > () = MapSizeType::Normal; }
#line 3167 "grammar.gen.tab.cpp"
    break;

  case 78:
#line 712 "grammar.gen.ypp"
                      { yylhs.value.as < MapSizeType > () = MapSizeType::Large; }
#line 3173 "grammar.gen.tab.cpp"
    break;

  case 79:
#line 713 "grammar.gen.ypp"
                      { yylhs.value.as < MapSizeType > () = MapSizeType::Giant; }
#line 3179 "grammar.gen.tab.cpp"
    break;

  case 80:
#line 716 "grammar.gen.ypp"
                       { yylhs.value.as < MapTypeName > () = MapTypeName::Arabia; }
#line 3185 "grammar.gen.tab.cpp"
    break;

  case 81:
#line 717 "grammar.gen.ypp"
                            { yylhs.value.as < MapTypeName > () = MapTypeName::Archipelago; }
#line 3191 "grammar.gen.tab.cpp"
    break;

  case 82:
#line 718 "grammar.gen.ypp"
                       { yylhs.value.as < MapTypeName > () = MapTypeName::Baltic; }
#line 3197 "grammar.gen.tab.cpp"
    break;

  case 83:
#line 719 "grammar.gen.ypp"
                            { yylhs.value.as < MapTypeName > () = MapTypeName::BlackForest; }
#line 3203 "grammar.gen.tab.cpp"
    break;

  case 84:
#line 720 "grammar.gen.ypp"
                        { yylhs.value.as < MapTypeName > () = MapTypeName::Coastal; }
#line 3209 "grammar.gen.tab.cpp"
    break;

  case 85:
#line 721 "grammar.gen.ypp"
                            { yylhs.value.as < MapTypeName > () = MapTypeName::Continental; }
#line 3215 "grammar.gen.tab.cpp"
    break;

  case 86:
#line 722 "grammar.gen.ypp"
                           { yylhs.value.as < MapTypeName > () = MapTypeName::CraterLake; }
#line 3221 "grammar.gen.tab.cpp"
    break;

  case 87:
#line 723 "grammar.gen.ypp"
                         { yylhs.value.as < MapTypeName > () = MapTypeName::Fortress; }
#line 3227 "grammar.gen.tab.cpp"
    break;

  case 88:
#line 724 "grammar.gen.ypp"
                         { yylhs.value.as < MapTypeName > () = MapTypeName::GoldRush; }
#line 3233 "grammar.gen.tab.cpp"
    break;

  case 89:
#line 725 "grammar.gen.ypp"
                         { yylhs.value.as < MapTypeName > () = MapTypeName::Highland; }
#line 3239 "grammar.gen.tab.cpp"
    break;

  case 90:
#line 726 "grammar.gen.ypp"
                        { yylhs.value.as < MapTypeName > () = MapTypeName::Islands; }
#line 3245 "grammar.gen.tab.cpp"
    break;

  case 91:
#line 727 "grammar.gen.ypp"
                              { yylhs.value.as < MapTypeName > () = MapTypeName::Mediterranean; }
#line 3251 "grammar.gen.tab.cpp"
    break;

  case 92:
#line 728 "grammar.gen.ypp"
                          { yylhs.value.as < MapTypeName > () = MapTypeName::Migration; }
#line 3257 "grammar.gen.tab.cpp"
    break;

  case 93:
#line 729 "grammar.gen.ypp"
                       { yylhs.value.as < MapTypeName > () = MapTypeName::Rivers; }
#line 3263 "grammar.gen.tab.cpp"
    break;

  case 94:
#line 730 "grammar.gen.ypp"
                            { yylhs.value.as < MapTypeName > () = MapTypeName::TeamIslands; }
#line 3269 "grammar.gen.tab.cpp"
    break;

  case 95:
#line 731 "grammar.gen.ypp"
                            { yylhs.value.as < MapTypeName > () = MapTypeName::ScenarioMap; }
#line 3275 "grammar.gen.tab.cpp"
    break;

  case 96:
#line 734 "grammar.gen.ypp"
                             { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyAlly; }
#line 3281 "grammar.gen.tab.cpp"
    break;

  case 97:
#line 735 "grammar.gen.ypp"
                                 { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyComputer; }
#line 3287 "grammar.gen.tab.cpp"
    break;

  case 98:
#line 736 "grammar.gen.ypp"
                                     { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyComputerAlly; }
#line 3293 "grammar.gen.tab.cpp"
    break;

  case 99:
#line 737 "grammar.gen.ypp"
                                      { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyComputerEnemy; }
#line 3299 "grammar.gen.tab.cpp"
    break;

  case 100:
#line 738 "grammar.gen.ypp"
                                        { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyComputerNeutral; }
#line 3305 "grammar.gen.tab.cpp"
    break;

  case 101:
#line 739 "grammar.gen.ypp"
                              { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyEnemy; }
#line 3311 "grammar.gen.tab.cpp"
    break;

  case 102:
#line 740 "grammar.gen.ypp"
                              { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyHuman; }
#line 3317 "grammar.gen.tab.cpp"
    break;

  case 103:
#line 741 "grammar.gen.ypp"
                                  { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyHumanAlly; }
#line 3323 "grammar.gen.tab.cpp"
    break;

  case 104:
#line 742 "grammar.gen.ypp"
                                   { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyHumanEnemy; }
#line 3329 "grammar.gen.tab.cpp"
    break;

  case 105:
#line 743 "grammar.gen.ypp"
                                     { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyHumanNeutral; }
#line 3335 "grammar.gen.tab.cpp"
    break;

  case 106:
#line 744 "grammar.gen.ypp"
                                { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::AnyNeutral; }
#line 3341 "grammar.gen.tab.cpp"
    break;

  case 107:
#line 745 "grammar.gen.ypp"
                               { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::EveryAlly; }
#line 3347 "grammar.gen.tab.cpp"
    break;

  case 108:
#line 746 "grammar.gen.ypp"
                                   { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::EveryComputer; }
#line 3353 "grammar.gen.tab.cpp"
    break;

  case 109:
#line 747 "grammar.gen.ypp"
                                { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::EveryEnemy; }
#line 3359 "grammar.gen.tab.cpp"
    break;

  case 110:
#line 748 "grammar.gen.ypp"
                                { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::EveryHuman; }
#line 3365 "grammar.gen.tab.cpp"
    break;

  case 111:
#line 749 "grammar.gen.ypp"
                                  { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::EveryNeutral; }
#line 3371 "grammar.gen.tab.cpp"
    break;

  case 112:
#line 750 "grammar.gen.ypp"
                                    { yylhs.value.as < PlayerNumberType > () = PlayerNumberType::MyPlayerNumber; }
#line 3377 "grammar.gen.tab.cpp"
    break;

  case 113:
#line 753 "grammar.gen.ypp"
                   { yylhs.value.as < RelOp > () = RelOp::LessThan; }
#line 3383 "grammar.gen.tab.cpp"
    break;

  case 114:
#line 754 "grammar.gen.ypp"
                      { yylhs.value.as < RelOp > () = RelOp::LessOrEqual; }
#line 3389 "grammar.gen.tab.cpp"
    break;

  case 115:
#line 755 "grammar.gen.ypp"
                      { yylhs.value.as < RelOp > () = RelOp::GreaterThan; }
#line 3395 "grammar.gen.tab.cpp"
    break;

  case 116:
#line 756 "grammar.gen.ypp"
                         { yylhs.value.as < RelOp > () = RelOp::GreaterOrEqual; }
#line 3401 "grammar.gen.tab.cpp"
    break;

  case 117:
#line 757 "grammar.gen.ypp"
                { yylhs.value.as < RelOp > () = RelOp::Equal; }
#line 3407 "grammar.gen.tab.cpp"
    break;

  case 118:
#line 758 "grammar.gen.ypp"
                   { yylhs.value.as < RelOp > () = RelOp::NotEqual; }
#line 3413 "grammar.gen.tab.cpp"
    break;

  case 119:
#line 761 "grammar.gen.ypp"
                            { yylhs.value.as < ResearchItem > () = ResearchItem::RiArbalest; }
#line 3419 "grammar.gen.tab.cpp"
    break;

  case 120:
#line 762 "grammar.gen.ypp"
                            { yylhs.value.as < ResearchItem > () = ResearchItem::RiCrossbow; }
#line 3425 "grammar.gen.tab.cpp"
    break;

  case 121:
#line 763 "grammar.gen.ypp"
                                   { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteSkirmisher; }
#line 3431 "grammar.gen.tab.cpp"
    break;

  case 122:
#line 764 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiHandCannon; }
#line 3437 "grammar.gen.tab.cpp"
    break;

  case 123:
#line 765 "grammar.gen.ypp"
                                      { yylhs.value.as < ResearchItem > () = ResearchItem::RiHeavyCavalryArcher; }
#line 3443 "grammar.gen.tab.cpp"
    break;

  case 124:
#line 766 "grammar.gen.ypp"
                            { yylhs.value.as < ResearchItem > () = ResearchItem::RiChampion; }
#line 3449 "grammar.gen.tab.cpp"
    break;

  case 125:
#line 767 "grammar.gen.ypp"
                                     { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteEagleWarrior; }
#line 3455 "grammar.gen.tab.cpp"
    break;

  case 126:
#line 768 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiHalberdier; }
#line 3461 "grammar.gen.tab.cpp"
    break;

  case 127:
#line 769 "grammar.gen.ypp"
                                 { yylhs.value.as < ResearchItem > () = ResearchItem::RiLongSwordsman; }
#line 3467 "grammar.gen.tab.cpp"
    break;

  case 128:
#line 770 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiManAtArms; }
#line 3473 "grammar.gen.tab.cpp"
    break;

  case 129:
#line 771 "grammar.gen.ypp"
                                   { yylhs.value.as < ResearchItem > () = ResearchItem::RiParthianTactics; }
#line 3479 "grammar.gen.tab.cpp"
    break;

  case 130:
#line 772 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiPikeman; }
#line 3485 "grammar.gen.tab.cpp"
    break;

  case 131:
#line 773 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiSquires; }
#line 3491 "grammar.gen.tab.cpp"
    break;

  case 132:
#line 774 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiThumbRing; }
#line 3497 "grammar.gen.tab.cpp"
    break;

  case 133:
#line 775 "grammar.gen.ypp"
                            { yylhs.value.as < ResearchItem > () = ResearchItem::RiTracking; }
#line 3503 "grammar.gen.tab.cpp"
    break;

  case 134:
#line 776 "grammar.gen.ypp"
                                      { yylhs.value.as < ResearchItem > () = ResearchItem::RiTwoHandedSwordsman; }
#line 3509 "grammar.gen.tab.cpp"
    break;

  case 135:
#line 777 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiBlastFurnace; }
#line 3515 "grammar.gen.tab.cpp"
    break;

  case 136:
#line 778 "grammar.gen.ypp"
                               { yylhs.value.as < ResearchItem > () = ResearchItem::RiBodkinArrow; }
#line 3521 "grammar.gen.tab.cpp"
    break;

  case 137:
#line 779 "grammar.gen.ypp"
                          { yylhs.value.as < ResearchItem > () = ResearchItem::RiBracer; }
#line 3527 "grammar.gen.tab.cpp"
    break;

  case 138:
#line 780 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiChainBarding; }
#line 3533 "grammar.gen.tab.cpp"
    break;

  case 139:
#line 781 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiChainMail; }
#line 3539 "grammar.gen.tab.cpp"
    break;

  case 140:
#line 782 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiFletching; }
#line 3545 "grammar.gen.tab.cpp"
    break;

  case 141:
#line 783 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiForging; }
#line 3551 "grammar.gen.tab.cpp"
    break;

  case 142:
#line 784 "grammar.gen.ypp"
                               { yylhs.value.as < ResearchItem > () = ResearchItem::RiIronCasting; }
#line 3557 "grammar.gen.tab.cpp"
    break;

  case 143:
#line 785 "grammar.gen.ypp"
                                      { yylhs.value.as < ResearchItem > () = ResearchItem::RiLeatherArcherArmor; }
#line 3563 "grammar.gen.tab.cpp"
    break;

  case 144:
#line 786 "grammar.gen.ypp"
                                     { yylhs.value.as < ResearchItem > () = ResearchItem::RiPaddedArcherArmor; }
#line 3569 "grammar.gen.tab.cpp"
    break;

  case 145:
#line 787 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiPlateBarding; }
#line 3575 "grammar.gen.tab.cpp"
    break;

  case 146:
#line 788 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiPlateMail; }
#line 3581 "grammar.gen.tab.cpp"
    break;

  case 147:
#line 789 "grammar.gen.ypp"
                                   { yylhs.value.as < ResearchItem > () = ResearchItem::RiRingArcherArmor; }
#line 3587 "grammar.gen.tab.cpp"
    break;

  case 148:
#line 790 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiScaleBarding; }
#line 3593 "grammar.gen.tab.cpp"
    break;

  case 149:
#line 791 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiScaleMail; }
#line 3599 "grammar.gen.tab.cpp"
    break;

  case 150:
#line 792 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiConscription; }
#line 3605 "grammar.gen.tab.cpp"
    break;

  case 151:
#line 793 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiHoardings; }
#line 3611 "grammar.gen.tab.cpp"
    break;

  case 152:
#line 794 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiSappers; }
#line 3617 "grammar.gen.tab.cpp"
    break;

  case 153:
#line 795 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteBerserk; }
#line 3623 "grammar.gen.tab.cpp"
    break;

  case 154:
#line 796 "grammar.gen.ypp"
                                   { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteCataphract; }
#line 3629 "grammar.gen.tab.cpp"
    break;

  case 155:
#line 797 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteChuKoNu; }
#line 3635 "grammar.gen.tab.cpp"
    break;

  case 156:
#line 798 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteHuskarl; }
#line 3641 "grammar.gen.tab.cpp"
    break;

  case 157:
#line 799 "grammar.gen.ypp"
                                  { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteJanissary; }
#line 3647 "grammar.gen.tab.cpp"
    break;

  case 158:
#line 800 "grammar.gen.ypp"
                                   { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteLongbowman; }
#line 3653 "grammar.gen.tab.cpp"
    break;

  case 159:
#line 801 "grammar.gen.ypp"
                                 { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteMameluke; }
#line 3659 "grammar.gen.tab.cpp"
    break;

  case 160:
#line 802 "grammar.gen.ypp"
                                 { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteMangudai; }
#line 3665 "grammar.gen.tab.cpp"
    break;

  case 161:
#line 803 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteSamurai; }
#line 3671 "grammar.gen.tab.cpp"
    break;

  case 162:
#line 804 "grammar.gen.ypp"
                                       { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteTeutonicKnight; }
#line 3677 "grammar.gen.tab.cpp"
    break;

  case 163:
#line 805 "grammar.gen.ypp"
                                       { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteThrowingAxeman; }
#line 3683 "grammar.gen.tab.cpp"
    break;

  case 164:
#line 806 "grammar.gen.ypp"
                                    { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteWarElephant; }
#line 3689 "grammar.gen.tab.cpp"
    break;

  case 165:
#line 807 "grammar.gen.ypp"
                                   { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteWoadRaider; }
#line 3695 "grammar.gen.tab.cpp"
    break;

  case 166:
#line 808 "grammar.gen.ypp"
                                     { yylhs.value.as < ResearchItem > () = ResearchItem::RiMyUniqueEliteUnit; }
#line 3701 "grammar.gen.tab.cpp"
    break;

  case 167:
#line 809 "grammar.gen.ypp"
                                    { yylhs.value.as < ResearchItem > () = ResearchItem::RiMyUniqueResearch; }
#line 3707 "grammar.gen.tab.cpp"
    break;

  case 168:
#line 810 "grammar.gen.ypp"
                                 { yylhs.value.as < ResearchItem > () = ResearchItem::RiCannonGalleon; }
#line 3713 "grammar.gen.tab.cpp"
    break;

  case 169:
#line 811 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiCareening; }
#line 3719 "grammar.gen.tab.cpp"
    break;

  case 170:
#line 812 "grammar.gen.ypp"
                            { yylhs.value.as < ResearchItem > () = ResearchItem::RiDeckGuns; }
#line 3725 "grammar.gen.tab.cpp"
    break;

  case 171:
#line 813 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiDryDock; }
#line 3731 "grammar.gen.tab.cpp"
    break;

  case 172:
#line 814 "grammar.gen.ypp"
                                 { yylhs.value.as < ResearchItem > () = ResearchItem::RiEliteLongboat; }
#line 3737 "grammar.gen.tab.cpp"
    break;

  case 173:
#line 815 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiFastFireShip; }
#line 3743 "grammar.gen.tab.cpp"
    break;

  case 174:
#line 816 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiGalleon; }
#line 3749 "grammar.gen.tab.cpp"
    break;

  case 175:
#line 817 "grammar.gen.ypp"
                                       { yylhs.value.as < ResearchItem > () = ResearchItem::RiHeavyDemolitionShip; }
#line 3755 "grammar.gen.tab.cpp"
    break;

  case 176:
#line 818 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiShipwright; }
#line 3761 "grammar.gen.tab.cpp"
    break;

  case 177:
#line 819 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiWarGalley; }
#line 3767 "grammar.gen.tab.cpp"
    break;

  case 178:
#line 820 "grammar.gen.ypp"
                          { yylhs.value.as < ResearchItem > () = ResearchItem::RiBowSaw; }
#line 3773 "grammar.gen.tab.cpp"
    break;

  case 179:
#line 821 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiDoubleBitAxe; }
#line 3779 "grammar.gen.tab.cpp"
    break;

  case 180:
#line 822 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiTwoManSaw; }
#line 3785 "grammar.gen.tab.cpp"
    break;

  case 181:
#line 823 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiBanking; }
#line 3791 "grammar.gen.tab.cpp"
    break;

  case 182:
#line 824 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiCaravan; }
#line 3797 "grammar.gen.tab.cpp"
    break;

  case 183:
#line 825 "grammar.gen.ypp"
                               { yylhs.value.as < ResearchItem > () = ResearchItem::RiCartography; }
#line 3803 "grammar.gen.tab.cpp"
    break;

  case 184:
#line 826 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiCoinage; }
#line 3809 "grammar.gen.tab.cpp"
    break;

  case 185:
#line 827 "grammar.gen.ypp"
                          { yylhs.value.as < ResearchItem > () = ResearchItem::RiGuilds; }
#line 3815 "grammar.gen.tab.cpp"
    break;

  case 186:
#line 828 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiCropRotation; }
#line 3821 "grammar.gen.tab.cpp"
    break;

  case 187:
#line 829 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiHeavyPlow; }
#line 3827 "grammar.gen.tab.cpp"
    break;

  case 188:
#line 830 "grammar.gen.ypp"
                               { yylhs.value.as < ResearchItem > () = ResearchItem::RiHorseCollar; }
#line 3833 "grammar.gen.tab.cpp"
    break;

  case 189:
#line 831 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiGoldMining; }
#line 3839 "grammar.gen.tab.cpp"
    break;

  case 190:
#line 832 "grammar.gen.ypp"
                                   { yylhs.value.as < ResearchItem > () = ResearchItem::RiGoldShaftMining; }
#line 3845 "grammar.gen.tab.cpp"
    break;

  case 191:
#line 833 "grammar.gen.ypp"
                               { yylhs.value.as < ResearchItem > () = ResearchItem::RiStoneMining; }
#line 3851 "grammar.gen.tab.cpp"
    break;

  case 192:
#line 834 "grammar.gen.ypp"
                                    { yylhs.value.as < ResearchItem > () = ResearchItem::RiStoneShaftMining; }
#line 3857 "grammar.gen.tab.cpp"
    break;

  case 193:
#line 835 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiAtonement; }
#line 3863 "grammar.gen.tab.cpp"
    break;

  case 194:
#line 836 "grammar.gen.ypp"
                                 { yylhs.value.as < ResearchItem > () = ResearchItem::RiBlockPrinting; }
#line 3869 "grammar.gen.tab.cpp"
    break;

  case 195:
#line 837 "grammar.gen.ypp"
                         { yylhs.value.as < ResearchItem > () = ResearchItem::RiFaith; }
#line 3875 "grammar.gen.tab.cpp"
    break;

  case 196:
#line 838 "grammar.gen.ypp"
                          { yylhs.value.as < ResearchItem > () = ResearchItem::RiFervor; }
#line 3881 "grammar.gen.tab.cpp"
    break;

  case 197:
#line 839 "grammar.gen.ypp"
                                  { yylhs.value.as < ResearchItem > () = ResearchItem::RiHerbalMedicine; }
#line 3887 "grammar.gen.tab.cpp"
    break;

  case 198:
#line 840 "grammar.gen.ypp"
                          { yylhs.value.as < ResearchItem > () = ResearchItem::RiHeresy; }
#line 3893 "grammar.gen.tab.cpp"
    break;

  case 199:
#line 841 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiIllumination; }
#line 3899 "grammar.gen.tab.cpp"
    break;

  case 200:
#line 842 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiRedemption; }
#line 3905 "grammar.gen.tab.cpp"
    break;

  case 201:
#line 843 "grammar.gen.ypp"
                            { yylhs.value.as < ResearchItem > () = ResearchItem::RiSanctity; }
#line 3911 "grammar.gen.tab.cpp"
    break;

  case 202:
#line 844 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiTheocracy; }
#line 3917 "grammar.gen.tab.cpp"
    break;

  case 203:
#line 845 "grammar.gen.ypp"
                                 { yylhs.value.as < ResearchItem > () = ResearchItem::RiBombardCannon; }
#line 3923 "grammar.gen.tab.cpp"
    break;

  case 204:
#line 846 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiCappedRam; }
#line 3929 "grammar.gen.tab.cpp"
    break;

  case 205:
#line 847 "grammar.gen.ypp"
                                 { yylhs.value.as < ResearchItem > () = ResearchItem::RiHeavyScorpion; }
#line 3935 "grammar.gen.tab.cpp"
    break;

  case 206:
#line 848 "grammar.gen.ypp"
                          { yylhs.value.as < ResearchItem > () = ResearchItem::RiOnager; }
#line 3941 "grammar.gen.tab.cpp"
    break;

  case 207:
#line 849 "grammar.gen.ypp"
                            { yylhs.value.as < ResearchItem > () = ResearchItem::RiScorpion; }
#line 3947 "grammar.gen.tab.cpp"
    break;

  case 208:
#line 850 "grammar.gen.ypp"
                               { yylhs.value.as < ResearchItem > () = ResearchItem::RiSiegeOnager; }
#line 3953 "grammar.gen.tab.cpp"
    break;

  case 209:
#line 851 "grammar.gen.ypp"
                            { yylhs.value.as < ResearchItem > () = ResearchItem::RiSiegeRam; }
#line 3959 "grammar.gen.tab.cpp"
    break;

  case 210:
#line 852 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiBloodlines; }
#line 3965 "grammar.gen.tab.cpp"
    break;

  case 211:
#line 853 "grammar.gen.ypp"
                            { yylhs.value.as < ResearchItem > () = ResearchItem::RiCavalier; }
#line 3971 "grammar.gen.tab.cpp"
    break;

  case 212:
#line 854 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiHeavyCamel; }
#line 3977 "grammar.gen.tab.cpp"
    break;

  case 213:
#line 855 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiHusbandry; }
#line 3983 "grammar.gen.tab.cpp"
    break;

  case 214:
#line 856 "grammar.gen.ypp"
                          { yylhs.value.as < ResearchItem > () = ResearchItem::RiHussar; }
#line 3989 "grammar.gen.tab.cpp"
    break;

  case 215:
#line 857 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiLightCavalry; }
#line 3995 "grammar.gen.tab.cpp"
    break;

  case 216:
#line 858 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiPaladin; }
#line 4001 "grammar.gen.tab.cpp"
    break;

  case 217:
#line 859 "grammar.gen.ypp"
                            { yylhs.value.as < ResearchItem > () = ResearchItem::RiHandCart; }
#line 4007 "grammar.gen.tab.cpp"
    break;

  case 218:
#line 860 "grammar.gen.ypp"
                        { yylhs.value.as < ResearchItem > () = ResearchItem::RiLoom; }
#line 4013 "grammar.gen.tab.cpp"
    break;

  case 219:
#line 861 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiTownPatrol; }
#line 4019 "grammar.gen.tab.cpp"
    break;

  case 220:
#line 862 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiTownWatch; }
#line 4025 "grammar.gen.tab.cpp"
    break;

  case 221:
#line 863 "grammar.gen.ypp"
                               { yylhs.value.as < ResearchItem > () = ResearchItem::RiWheelBarrow; }
#line 4031 "grammar.gen.tab.cpp"
    break;

  case 222:
#line 864 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiArchitecture; }
#line 4037 "grammar.gen.tab.cpp"
    break;

  case 223:
#line 865 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiBallistics; }
#line 4043 "grammar.gen.tab.cpp"
    break;

  case 224:
#line 866 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiBombardTower; }
#line 4049 "grammar.gen.tab.cpp"
    break;

  case 225:
#line 867 "grammar.gen.ypp"
                             { yylhs.value.as < ResearchItem > () = ResearchItem::RiChemistry; }
#line 4055 "grammar.gen.tab.cpp"
    break;

  case 226:
#line 868 "grammar.gen.ypp"
                                 { yylhs.value.as < ResearchItem > () = ResearchItem::RiFortifiedWall; }
#line 4061 "grammar.gen.tab.cpp"
    break;

  case 227:
#line 869 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiGuardTower; }
#line 4067 "grammar.gen.tab.cpp"
    break;

  case 228:
#line 870 "grammar.gen.ypp"
                              { yylhs.value.as < ResearchItem > () = ResearchItem::RiHeatedShot; }
#line 4073 "grammar.gen.tab.cpp"
    break;

  case 229:
#line 871 "grammar.gen.ypp"
                        { yylhs.value.as < ResearchItem > () = ResearchItem::RiKeep; }
#line 4079 "grammar.gen.tab.cpp"
    break;

  case 230:
#line 872 "grammar.gen.ypp"
                           { yylhs.value.as < ResearchItem > () = ResearchItem::RiMasonry; }
#line 4085 "grammar.gen.tab.cpp"
    break;

  case 231:
#line 873 "grammar.gen.ypp"
                               { yylhs.value.as < ResearchItem > () = ResearchItem::RiMurderHoles; }
#line 4091 "grammar.gen.tab.cpp"
    break;

  case 232:
#line 874 "grammar.gen.ypp"
                                  { yylhs.value.as < ResearchItem > () = ResearchItem::RiSiegeEngineers; }
#line 4097 "grammar.gen.tab.cpp"
    break;

  case 233:
#line 875 "grammar.gen.ypp"
                                { yylhs.value.as < ResearchItem > () = ResearchItem::RiStonecutting; }
#line 4103 "grammar.gen.tab.cpp"
    break;

  case 234:
#line 876 "grammar.gen.ypp"
                                     { yylhs.value.as < ResearchItem > () = ResearchItem::MyUniqueUnitUpgrade; }
#line 4109 "grammar.gen.tab.cpp"
    break;

  case 235:
#line 877 "grammar.gen.ypp"
                                  { yylhs.value.as < ResearchItem > () = ResearchItem::MyUniqueResearch; }
#line 4115 "grammar.gen.tab.cpp"
    break;

  case 236:
#line 880 "grammar.gen.ypp"
                                       { yylhs.value.as < StartingResourcesType > () = StartingResourcesType::LowResources; }
#line 4121 "grammar.gen.tab.cpp"
    break;

  case 237:
#line 881 "grammar.gen.ypp"
                                          { yylhs.value.as < StartingResourcesType > () = StartingResourcesType::MediumResources; }
#line 4127 "grammar.gen.tab.cpp"
    break;

  case 238:
#line 882 "grammar.gen.ypp"
                                        { yylhs.value.as < StartingResourcesType > () = StartingResourcesType::HighResources; }
#line 4133 "grammar.gen.tab.cpp"
    break;

  case 239:
#line 885 "grammar.gen.ypp"
                                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnPercentCivilianExplorers; }
#line 4139 "grammar.gen.tab.cpp"
    break;

  case 240:
#line 886 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnPercentCivilianBuilders; }
#line 4145 "grammar.gen.tab.cpp"
    break;

  case 241:
#line 887 "grammar.gen.ypp"
                                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnPercentCivilianGatherers; }
#line 4151 "grammar.gen.tab.cpp"
    break;

  case 242:
#line 888 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnCapCivilianExplorers; }
#line 4157 "grammar.gen.tab.cpp"
    break;

  case 243:
#line 889 "grammar.gen.ypp"
                                              { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnCapCivilianBuilders; }
#line 4163 "grammar.gen.tab.cpp"
    break;

  case 244:
#line 890 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnCapCivilianGatherers; }
#line 4169 "grammar.gen.tab.cpp"
    break;

  case 245:
#line 891 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumAttackGroupSize; }
#line 4175 "grammar.gen.tab.cpp"
    break;

  case 246:
#line 892 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTotalNumberExplorers; }
#line 4181 "grammar.gen.tab.cpp"
    break;

  case 247:
#line 893 "grammar.gen.ypp"
                                                      { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnPercentEnemySightedResponse; }
#line 4187 "grammar.gen.tab.cpp"
    break;

  case 248:
#line 894 "grammar.gen.ypp"
                                                       { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnEnemySightedResponseDistance; }
#line 4193 "grammar.gen.tab.cpp"
    break;

  case 249:
#line 895 "grammar.gen.ypp"
                                         { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnSentryDistance; }
#line 4199 "grammar.gen.tab.cpp"
    break;

  case 250:
#line 896 "grammar.gen.ypp"
                                              { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnRelicReturnDistance; }
#line 4205 "grammar.gen.tab.cpp"
    break;

  case 251:
#line 897 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumDefendGroupSize; }
#line 4211 "grammar.gen.tab.cpp"
    break;

  case 252:
#line 898 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumAttackGroupSize; }
#line 4217 "grammar.gen.tab.cpp"
    break;

  case 253:
#line 899 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumDefendGroupSize; }
#line 4223 "grammar.gen.tab.cpp"
    break;

  case 254:
#line 900 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumPeaceLikeLevel; }
#line 4229 "grammar.gen.tab.cpp"
    break;

  case 255:
#line 901 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnPercentExplorationRequired; }
#line 4235 "grammar.gen.tab.cpp"
    break;

  case 256:
#line 902 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnZeroPriorityDistance; }
#line 4241 "grammar.gen.tab.cpp"
    break;

  case 257:
#line 903 "grammar.gen.ypp"
                                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumCivilianExplorers; }
#line 4247 "grammar.gen.tab.cpp"
    break;

  case 258:
#line 904 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnNumberAttackGroups; }
#line 4253 "grammar.gen.tab.cpp"
    break;

  case 259:
#line 905 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnNumberDefendGroups; }
#line 4259 "grammar.gen.tab.cpp"
    break;

  case 260:
#line 906 "grammar.gen.ypp"
                                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnAttackGroupGatherSpacing; }
#line 4265 "grammar.gen.tab.cpp"
    break;

  case 261:
#line 907 "grammar.gen.ypp"
                                              { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnNumberExploreGroups; }
#line 4271 "grammar.gen.tab.cpp"
    break;

  case 262:
#line 908 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumExploreGroupSize; }
#line 4277 "grammar.gen.tab.cpp"
    break;

  case 263:
#line 909 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumExploreGroupSize; }
#line 4283 "grammar.gen.tab.cpp"
    break;

  case 264:
#line 910 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnGoldDefendPriority; }
#line 4289 "grammar.gen.tab.cpp"
    break;

  case 265:
#line 911 "grammar.gen.ypp"
                                              { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnStoneDefendPriority; }
#line 4295 "grammar.gen.tab.cpp"
    break;

  case 266:
#line 912 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnForageDefendPriority; }
#line 4301 "grammar.gen.tab.cpp"
    break;

  case 267:
#line 913 "grammar.gen.ypp"
                                              { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnRelicDefendPriority; }
#line 4307 "grammar.gen.tab.cpp"
    break;

  case 268:
#line 914 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTownDefendPriority; }
#line 4313 "grammar.gen.tab.cpp"
    break;

  case 269:
#line 915 "grammar.gen.ypp"
                                          { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnDefenseDistance; }
#line 4319 "grammar.gen.tab.cpp"
    break;

  case 270:
#line 916 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnNumberBoatAttackGroups; }
#line 4325 "grammar.gen.tab.cpp"
    break;

  case 271:
#line 917 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumBoatAttackGroupSize; }
#line 4331 "grammar.gen.tab.cpp"
    break;

  case 272:
#line 918 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumBoatAttackGroupSize; }
#line 4337 "grammar.gen.tab.cpp"
    break;

  case 273:
#line 919 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnNumberBoatExploreGroups; }
#line 4343 "grammar.gen.tab.cpp"
    break;

  case 274:
#line 920 "grammar.gen.ypp"
                                                      { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumBoatExploreGroupSize; }
#line 4349 "grammar.gen.tab.cpp"
    break;

  case 275:
#line 921 "grammar.gen.ypp"
                                                      { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumBoatExploreGroupSize; }
#line 4355 "grammar.gen.tab.cpp"
    break;

  case 276:
#line 922 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnNumberBoatDefendGroups; }
#line 4361 "grammar.gen.tab.cpp"
    break;

  case 277:
#line 923 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumBoatDefendGroupSize; }
#line 4367 "grammar.gen.tab.cpp"
    break;

  case 278:
#line 924 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumBoatDefendGroupSize; }
#line 4373 "grammar.gen.tab.cpp"
    break;

  case 279:
#line 925 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnDockDefendPriority; }
#line 4379 "grammar.gen.tab.cpp"
    break;

  case 280:
#line 926 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnSentryDistanceVariation; }
#line 4385 "grammar.gen.tab.cpp"
    break;

  case 281:
#line 927 "grammar.gen.ypp"
                                          { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumTownSize; }
#line 4391 "grammar.gen.tab.cpp"
    break;

  case 282:
#line 928 "grammar.gen.ypp"
                                          { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumTownSize; }
#line 4397 "grammar.gen.tab.cpp"
    break;

  case 283:
#line 929 "grammar.gen.ypp"
                                                        { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnGroupCommanderSelectionMethod; }
#line 4403 "grammar.gen.tab.cpp"
    break;

  case 284:
#line 930 "grammar.gen.ypp"
                                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnConsecutiveIdleUnitLimit; }
#line 4409 "grammar.gen.tab.cpp"
    break;

  case 285:
#line 931 "grammar.gen.ypp"
                                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationDistance; }
#line 4415 "grammar.gen.tab.cpp"
    break;

  case 286:
#line 932 "grammar.gen.ypp"
                                                    { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationHitpoints; }
#line 4421 "grammar.gen.tab.cpp"
    break;

  case 287:
#line 933 "grammar.gen.ypp"
                                                           { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationDamageCapability; }
#line 4427 "grammar.gen.tab.cpp"
    break;

  case 288:
#line 934 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationKills; }
#line 4433 "grammar.gen.tab.cpp"
    break;

  case 289:
#line 935 "grammar.gen.ypp"
                                                        { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationAllyProximity; }
#line 4439 "grammar.gen.tab.cpp"
    break;

  case 290:
#line 936 "grammar.gen.ypp"
                                              { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationRof; }
#line 4445 "grammar.gen.tab.cpp"
    break;

  case 291:
#line 937 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationRandomness; }
#line 4451 "grammar.gen.tab.cpp"
    break;

  case 292:
#line 938 "grammar.gen.ypp"
                                          { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnCampMaxDistance; }
#line 4457 "grammar.gen.tab.cpp"
    break;

  case 293:
#line 939 "grammar.gen.ypp"
                                          { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMillMaxDistance; }
#line 4463 "grammar.gen.tab.cpp"
    break;

  case 294:
#line 940 "grammar.gen.ypp"
                                                         { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationAttackAttempts; }
#line 4469 "grammar.gen.tab.cpp"
    break;

  case 295:
#line 941 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationRange; }
#line 4475 "grammar.gen.tab.cpp"
    break;

  case 296:
#line 942 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnDefendOverlapDistance; }
#line 4481 "grammar.gen.tab.cpp"
    break;

  case 297:
#line 943 "grammar.gen.ypp"
                                                      { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnScaleMinimumAttackGroupSize; }
#line 4487 "grammar.gen.tab.cpp"
    break;

  case 298:
#line 944 "grammar.gen.ypp"
                                                      { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnScaleMaximumAttackGroupSize; }
#line 4493 "grammar.gen.tab.cpp"
    break;

  case 299:
#line 945 "grammar.gen.ypp"
                                                    { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnAttackGroupSizeRandomness; }
#line 4499 "grammar.gen.tab.cpp"
    break;

  case 300:
#line 946 "grammar.gen.ypp"
                                           { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnScalingFrequency; }
#line 4505 "grammar.gen.tab.cpp"
    break;

  case 301:
#line 947 "grammar.gen.ypp"
                                                    { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumGaiaAttackResponse; }
#line 4511 "grammar.gen.tab.cpp"
    break;

  case 302:
#line 948 "grammar.gen.ypp"
                                         { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnBuildFrequency; }
#line 4517 "grammar.gen.tab.cpp"
    break;

  case 303:
#line 949 "grammar.gen.ypp"
                                                         { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnAttackSeparationTimeRandomness; }
#line 4523 "grammar.gen.tab.cpp"
    break;

  case 304:
#line 950 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnAttackIntelligence; }
#line 4529 "grammar.gen.tab.cpp"
    break;

  case 305:
#line 951 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnInitialAttackDelay; }
#line 4535 "grammar.gen.tab.cpp"
    break;

  case 306:
#line 952 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnSaveScenarioInformation; }
#line 4541 "grammar.gen.tab.cpp"
    break;

  case 307:
#line 953 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnSpecialAttackType1; }
#line 4547 "grammar.gen.tab.cpp"
    break;

  case 308:
#line 954 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnSpecialAttackInfluence1; }
#line 4553 "grammar.gen.tab.cpp"
    break;

  case 309:
#line 955 "grammar.gen.ypp"
                                                      { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumWaterBodySizeForDock; }
#line 4559 "grammar.gen.tab.cpp"
    break;

  case 310:
#line 956 "grammar.gen.ypp"
                                                        { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnNumberBuildAttemptsBeforeSkip; }
#line 4565 "grammar.gen.tab.cpp"
    break;

  case 311:
#line 957 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaxSkipsPerAttempt; }
#line 4571 "grammar.gen.tab.cpp"
    break;

  case 312:
#line 958 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnFoodGathererPercentage; }
#line 4577 "grammar.gen.tab.cpp"
    break;

  case 313:
#line 959 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnGoldGathererPercentage; }
#line 4583 "grammar.gen.tab.cpp"
    break;

  case 314:
#line 960 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnStoneGathererPercentage; }
#line 4589 "grammar.gen.tab.cpp"
    break;

  case 315:
#line 961 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnWoodGathererPercentage; }
#line 4595 "grammar.gen.tab.cpp"
    break;

  case 316:
#line 962 "grammar.gen.ypp"
                                                    { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationContinent; }
#line 4601 "grammar.gen.tab.cpp"
    break;

  case 317:
#line 963 "grammar.gen.ypp"
                                                      { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationSiegeWeapon; }
#line 4607 "grammar.gen.tab.cpp"
    break;

  case 318:
#line 964 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnGroupLeaderDefenseDistance; }
#line 4613 "grammar.gen.tab.cpp"
    break;

  case 319:
#line 965 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnInitialAttackDelayType; }
#line 4619 "grammar.gen.tab.cpp"
    break;

  case 320:
#line 966 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnBlotExplorationMap; }
#line 4625 "grammar.gen.tab.cpp"
    break;

  case 321:
#line 967 "grammar.gen.ypp"
                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnBlotSize; }
#line 4631 "grammar.gen.tab.cpp"
    break;

  case 322:
#line 968 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnIntelligentGathering; }
#line 4637 "grammar.gen.tab.cpp"
    break;

  case 323:
#line 969 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTaskUngroupedSoldiers; }
#line 4643 "grammar.gen.tab.cpp"
    break;

  case 324:
#line 970 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationBoat; }
#line 4649 "grammar.gen.tab.cpp"
    break;

  case 325:
#line 971 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnNumberEnemyObjectsRequired; }
#line 4655 "grammar.gen.tab.cpp"
    break;

  case 326:
#line 972 "grammar.gen.ypp"
                                              { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnNumberMaxSkipCycles; }
#line 4661 "grammar.gen.tab.cpp"
    break;

  case 327:
#line 973 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnRetaskGatherAmount; }
#line 4667 "grammar.gen.tab.cpp"
    break;

  case 328:
#line 974 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaxRetaskGatherAmount; }
#line 4673 "grammar.gen.tab.cpp"
    break;

  case 329:
#line 975 "grammar.gen.ypp"
                                                         { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaxBuildPlanGathererPercentage; }
#line 4679 "grammar.gen.tab.cpp"
    break;

  case 330:
#line 976 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnFoodDropsiteDistance; }
#line 4685 "grammar.gen.tab.cpp"
    break;

  case 331:
#line 977 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnWoodDropsiteDistance; }
#line 4691 "grammar.gen.tab.cpp"
    break;

  case 332:
#line 978 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnStoneDropsiteDistance; }
#line 4697 "grammar.gen.tab.cpp"
    break;

  case 333:
#line 979 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnGoldDropsiteDistance; }
#line 4703 "grammar.gen.tab.cpp"
    break;

  case 334:
#line 980 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnInitialExplorationRequired; }
#line 4709 "grammar.gen.tab.cpp"
    break;

  case 335:
#line 981 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnRandomPlacementFactor; }
#line 4715 "grammar.gen.tab.cpp"
    break;

  case 336:
#line 982 "grammar.gen.ypp"
                                              { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnRequiredForestTiles; }
#line 4721 "grammar.gen.tab.cpp"
    break;

  case 337:
#line 983 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnAttackDiplomacyImpact; }
#line 4727 "grammar.gen.tab.cpp"
    break;

  case 338:
#line 984 "grammar.gen.ypp"
                                                 { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnPercentHalfExploration; }
#line 4733 "grammar.gen.tab.cpp"
    break;

  case 339:
#line 985 "grammar.gen.ypp"
                                                        { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationTimeKillRatio; }
#line 4739 "grammar.gen.tab.cpp"
    break;

  case 340:
#line 986 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTargetEvaluationInProgress; }
#line 4745 "grammar.gen.tab.cpp"
    break;

  case 341:
#line 987 "grammar.gen.ypp"
                                              { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnAttackWinningPlayer; }
#line 4751 "grammar.gen.tab.cpp"
    break;

  case 342:
#line 988 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnCoopShareInformation; }
#line 4757 "grammar.gen.tab.cpp"
    break;

  case 343:
#line 989 "grammar.gen.ypp"
                                                    { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnAttackWinningPlayerFactor; }
#line 4763 "grammar.gen.tab.cpp"
    break;

  case 344:
#line 990 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnCoopShareAttacking; }
#line 4769 "grammar.gen.tab.cpp"
    break;

  case 345:
#line 991 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnCoopShareAttackingInterval; }
#line 4775 "grammar.gen.tab.cpp"
    break;

  case 346:
#line 992 "grammar.gen.ypp"
                                                         { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnPercentageExploreExterminators; }
#line 4781 "grammar.gen.tab.cpp"
    break;

  case 347:
#line 993 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnTrackPlayerHistory; }
#line 4787 "grammar.gen.tab.cpp"
    break;

  case 348:
#line 994 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumDropsiteBuffer; }
#line 4793 "grammar.gen.tab.cpp"
    break;

  case 349:
#line 995 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnUseByTypeMaxGathering; }
#line 4799 "grammar.gen.tab.cpp"
    break;

  case 350:
#line 996 "grammar.gen.ypp"
                                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumBoarHuntGroupSize; }
#line 4805 "grammar.gen.tab.cpp"
    break;

  case 351:
#line 997 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMinimumAmountForTrading; }
#line 4811 "grammar.gen.tab.cpp"
    break;

  case 352:
#line 998 "grammar.gen.ypp"
                                                    { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnEasiestReactionPercentage; }
#line 4817 "grammar.gen.tab.cpp"
    break;

  case 353:
#line 999 "grammar.gen.ypp"
                                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnEasierReactionPercentage; }
#line 4823 "grammar.gen.tab.cpp"
    break;

  case 354:
#line 1000 "grammar.gen.ypp"
                                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnHitsBeforeAllianceChange; }
#line 4829 "grammar.gen.tab.cpp"
    break;

  case 355:
#line 1001 "grammar.gen.ypp"
                                               { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnAllowCivilianDefense; }
#line 4835 "grammar.gen.tab.cpp"
    break;

  case 356:
#line 1002 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnNumberForwardBuilders; }
#line 4841 "grammar.gen.tab.cpp"
    break;

  case 357:
#line 1003 "grammar.gen.ypp"
                                                { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnPercentAttackSoldiers; }
#line 4847 "grammar.gen.tab.cpp"
    break;

  case 358:
#line 1004 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnPercentAttackBoats; }
#line 4853 "grammar.gen.tab.cpp"
    break;

  case 359:
#line 1005 "grammar.gen.ypp"
                                                       { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnDoNotScaleForDifficultyLevel; }
#line 4859 "grammar.gen.tab.cpp"
    break;

  case 360:
#line 1006 "grammar.gen.ypp"
                                            { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnGroupFormDistance; }
#line 4865 "grammar.gen.tab.cpp"
    break;

  case 361:
#line 1007 "grammar.gen.ypp"
                                                       { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnIgnoreAttackGroupUnderAttack; }
#line 4871 "grammar.gen.tab.cpp"
    break;

  case 362:
#line 1008 "grammar.gen.ypp"
                                             { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnGatherDefenseUnits; }
#line 4877 "grammar.gen.tab.cpp"
    break;

  case 363:
#line 1009 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumWoodDropDistance; }
#line 4883 "grammar.gen.tab.cpp"
    break;

  case 364:
#line 1010 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumFoodDropDistance; }
#line 4889 "grammar.gen.tab.cpp"
    break;

  case 365:
#line 1011 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumHuntDropDistance; }
#line 4895 "grammar.gen.tab.cpp"
    break;

  case 366:
#line 1012 "grammar.gen.ypp"
                                                      { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumFishBoatDropDistance; }
#line 4901 "grammar.gen.tab.cpp"
    break;

  case 367:
#line 1013 "grammar.gen.ypp"
                                                  { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumGoldDropDistance; }
#line 4907 "grammar.gen.tab.cpp"
    break;

  case 368:
#line 1014 "grammar.gen.ypp"
                                                   { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnMaximumStoneDropDistance; }
#line 4913 "grammar.gen.tab.cpp"
    break;

  case 369:
#line 1015 "grammar.gen.ypp"
                                                     { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnGatherIdleSoldiersAtCenter; }
#line 4919 "grammar.gen.tab.cpp"
    break;

  case 370:
#line 1016 "grammar.gen.ypp"
                                       { yylhs.value.as < StrategicNumberName > () = StrategicNumberName::SnGarrisonRams; }
#line 4925 "grammar.gen.tab.cpp"
    break;

  case 371:
#line 1019 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::Arbalest; }
#line 4931 "grammar.gen.tab.cpp"
    break;

  case 372:
#line 1020 "grammar.gen.ypp"
                { yylhs.value.as < Unit > () = Unit::Archer; }
#line 4937 "grammar.gen.tab.cpp"
    break;

  case 373:
#line 1021 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::CavalryArcher; }
#line 4943 "grammar.gen.tab.cpp"
    break;

  case 374:
#line 1022 "grammar.gen.ypp"
                     { yylhs.value.as < Unit > () = Unit::Crossbowman; }
#line 4949 "grammar.gen.tab.cpp"
    break;

  case 375:
#line 1023 "grammar.gen.ypp"
                         { yylhs.value.as < Unit > () = Unit::EliteSkirmisher; }
#line 4955 "grammar.gen.tab.cpp"
    break;

  case 376:
#line 1024 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::HandCannoneer; }
#line 4961 "grammar.gen.tab.cpp"
    break;

  case 377:
#line 1025 "grammar.gen.ypp"
                            { yylhs.value.as < Unit > () = Unit::HeavyCavalryArcher; }
#line 4967 "grammar.gen.tab.cpp"
    break;

  case 378:
#line 1026 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::Skirmisher; }
#line 4973 "grammar.gen.tab.cpp"
    break;

  case 379:
#line 1027 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::Champion; }
#line 4979 "grammar.gen.tab.cpp"
    break;

  case 380:
#line 1028 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::EagleWarrior; }
#line 4985 "grammar.gen.tab.cpp"
    break;

  case 381:
#line 1029 "grammar.gen.ypp"
                           { yylhs.value.as < Unit > () = Unit::EliteEagleWarrior; }
#line 4991 "grammar.gen.tab.cpp"
    break;

  case 382:
#line 1030 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::Halberdier; }
#line 4997 "grammar.gen.tab.cpp"
    break;

  case 383:
#line 1031 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::LongSwordsman; }
#line 5003 "grammar.gen.tab.cpp"
    break;

  case 384:
#line 1032 "grammar.gen.ypp"
                   { yylhs.value.as < Unit > () = Unit::ManAtArms; }
#line 5009 "grammar.gen.tab.cpp"
    break;

  case 385:
#line 1033 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::Militiaman; }
#line 5015 "grammar.gen.tab.cpp"
    break;

  case 386:
#line 1034 "grammar.gen.ypp"
                 { yylhs.value.as < Unit > () = Unit::Pikeman; }
#line 5021 "grammar.gen.tab.cpp"
    break;

  case 387:
#line 1035 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::Spearman; }
#line 5027 "grammar.gen.tab.cpp"
    break;

  case 388:
#line 1036 "grammar.gen.ypp"
                            { yylhs.value.as < Unit > () = Unit::TwoHandedSwordsman; }
#line 5033 "grammar.gen.tab.cpp"
    break;

  case 389:
#line 1037 "grammar.gen.ypp"
                 { yylhs.value.as < Unit > () = Unit::Berserk; }
#line 5039 "grammar.gen.tab.cpp"
    break;

  case 390:
#line 1038 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::Cataphract; }
#line 5045 "grammar.gen.tab.cpp"
    break;

  case 391:
#line 1039 "grammar.gen.ypp"
                 { yylhs.value.as < Unit > () = Unit::ChuKoNu; }
#line 5051 "grammar.gen.tab.cpp"
    break;

  case 392:
#line 1040 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::Conquistador; }
#line 5057 "grammar.gen.tab.cpp"
    break;

  case 393:
#line 1041 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::EliteBerserk; }
#line 5063 "grammar.gen.tab.cpp"
    break;

  case 394:
#line 1042 "grammar.gen.ypp"
                         { yylhs.value.as < Unit > () = Unit::EliteCataphract; }
#line 5069 "grammar.gen.tab.cpp"
    break;

  case 395:
#line 1043 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::EliteChuKoNu; }
#line 5075 "grammar.gen.tab.cpp"
    break;

  case 396:
#line 1044 "grammar.gen.ypp"
                           { yylhs.value.as < Unit > () = Unit::EliteConquistador; }
#line 5081 "grammar.gen.tab.cpp"
    break;

  case 397:
#line 1045 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::EliteHuskarl; }
#line 5087 "grammar.gen.tab.cpp"
    break;

  case 398:
#line 1046 "grammar.gen.ypp"
                            { yylhs.value.as < Unit > () = Unit::EliteJaguarWarrior; }
#line 5093 "grammar.gen.tab.cpp"
    break;

  case 399:
#line 1047 "grammar.gen.ypp"
                        { yylhs.value.as < Unit > () = Unit::EliteJanissary; }
#line 5099 "grammar.gen.tab.cpp"
    break;

  case 400:
#line 1048 "grammar.gen.ypp"
                         { yylhs.value.as < Unit > () = Unit::EliteLongbowman; }
#line 5105 "grammar.gen.tab.cpp"
    break;

  case 401:
#line 1049 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::EliteMameluke; }
#line 5111 "grammar.gen.tab.cpp"
    break;

  case 402:
#line 1050 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::EliteMangudai; }
#line 5117 "grammar.gen.tab.cpp"
    break;

  case 403:
#line 1051 "grammar.gen.ypp"
                           { yylhs.value.as < Unit > () = Unit::ElitePlumedArcher; }
#line 5123 "grammar.gen.tab.cpp"
    break;

  case 404:
#line 1052 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::EliteSamurai; }
#line 5129 "grammar.gen.tab.cpp"
    break;

  case 405:
#line 1053 "grammar.gen.ypp"
                     { yylhs.value.as < Unit > () = Unit::EliteTarkan; }
#line 5135 "grammar.gen.tab.cpp"
    break;

  case 406:
#line 1054 "grammar.gen.ypp"
                             { yylhs.value.as < Unit > () = Unit::EliteTeutonicKnight; }
#line 5141 "grammar.gen.tab.cpp"
    break;

  case 407:
#line 1055 "grammar.gen.ypp"
                             { yylhs.value.as < Unit > () = Unit::EliteThrowingAxeman; }
#line 5147 "grammar.gen.tab.cpp"
    break;

  case 408:
#line 1056 "grammar.gen.ypp"
                          { yylhs.value.as < Unit > () = Unit::EliteWarElephant; }
#line 5153 "grammar.gen.tab.cpp"
    break;

  case 409:
#line 1057 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::EliteWarWagon; }
#line 5159 "grammar.gen.tab.cpp"
    break;

  case 410:
#line 1058 "grammar.gen.ypp"
                         { yylhs.value.as < Unit > () = Unit::EliteWoadRaider; }
#line 5165 "grammar.gen.tab.cpp"
    break;

  case 411:
#line 1059 "grammar.gen.ypp"
                 { yylhs.value.as < Unit > () = Unit::Huskarl; }
#line 5171 "grammar.gen.tab.cpp"
    break;

  case 412:
#line 1060 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::JaguarWarrior; }
#line 5177 "grammar.gen.tab.cpp"
    break;

  case 413:
#line 1061 "grammar.gen.ypp"
                   { yylhs.value.as < Unit > () = Unit::Janissary; }
#line 5183 "grammar.gen.tab.cpp"
    break;

  case 414:
#line 1062 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::Longbowman; }
#line 5189 "grammar.gen.tab.cpp"
    break;

  case 415:
#line 1063 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::Mameluke; }
#line 5195 "grammar.gen.tab.cpp"
    break;

  case 416:
#line 1064 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::Mangudai; }
#line 5201 "grammar.gen.tab.cpp"
    break;

  case 417:
#line 1065 "grammar.gen.ypp"
                { yylhs.value.as < Unit > () = Unit::Petard; }
#line 5207 "grammar.gen.tab.cpp"
    break;

  case 418:
#line 1066 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::PlumedArcher; }
#line 5213 "grammar.gen.tab.cpp"
    break;

  case 419:
#line 1067 "grammar.gen.ypp"
                 { yylhs.value.as < Unit > () = Unit::Samurai; }
#line 5219 "grammar.gen.tab.cpp"
    break;

  case 420:
#line 1068 "grammar.gen.ypp"
                { yylhs.value.as < Unit > () = Unit::Tarkan; }
#line 5225 "grammar.gen.tab.cpp"
    break;

  case 421:
#line 1069 "grammar.gen.ypp"
                        { yylhs.value.as < Unit > () = Unit::TeutonicKnight; }
#line 5231 "grammar.gen.tab.cpp"
    break;

  case 422:
#line 1070 "grammar.gen.ypp"
                        { yylhs.value.as < Unit > () = Unit::ThrowingAxeman; }
#line 5237 "grammar.gen.tab.cpp"
    break;

  case 423:
#line 1071 "grammar.gen.ypp"
                   { yylhs.value.as < Unit > () = Unit::Trebuchet; }
#line 5243 "grammar.gen.tab.cpp"
    break;

  case 424:
#line 1072 "grammar.gen.ypp"
                     { yylhs.value.as < Unit > () = Unit::WarElephant; }
#line 5249 "grammar.gen.tab.cpp"
    break;

  case 425:
#line 1073 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::WarWagon; }
#line 5255 "grammar.gen.tab.cpp"
    break;

  case 426:
#line 1074 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::WoadRaider; }
#line 5261 "grammar.gen.tab.cpp"
    break;

  case 427:
#line 1075 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::CannonGalleon; }
#line 5267 "grammar.gen.tab.cpp"
    break;

  case 428:
#line 1076 "grammar.gen.ypp"
                        { yylhs.value.as < Unit > () = Unit::DemolitionShip; }
#line 5273 "grammar.gen.tab.cpp"
    break;

  case 429:
#line 1077 "grammar.gen.ypp"
                            { yylhs.value.as < Unit > () = Unit::EliteCannonGalleon; }
#line 5279 "grammar.gen.tab.cpp"
    break;

  case 430:
#line 1078 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::EliteLongboat; }
#line 5285 "grammar.gen.tab.cpp"
    break;

  case 431:
#line 1079 "grammar.gen.ypp"
                         { yylhs.value.as < Unit > () = Unit::EliteTurtleShip; }
#line 5291 "grammar.gen.tab.cpp"
    break;

  case 432:
#line 1080 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::FastFireShip; }
#line 5297 "grammar.gen.tab.cpp"
    break;

  case 433:
#line 1081 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::FireShip; }
#line 5303 "grammar.gen.tab.cpp"
    break;

  case 434:
#line 1082 "grammar.gen.ypp"
                     { yylhs.value.as < Unit > () = Unit::FishingShip; }
#line 5309 "grammar.gen.tab.cpp"
    break;

  case 435:
#line 1083 "grammar.gen.ypp"
                 { yylhs.value.as < Unit > () = Unit::Galleon; }
#line 5315 "grammar.gen.tab.cpp"
    break;

  case 436:
#line 1084 "grammar.gen.ypp"
                { yylhs.value.as < Unit > () = Unit::Galley; }
#line 5321 "grammar.gen.tab.cpp"
    break;

  case 437:
#line 1085 "grammar.gen.ypp"
                             { yylhs.value.as < Unit > () = Unit::HeavyDemolitionShip; }
#line 5327 "grammar.gen.tab.cpp"
    break;

  case 438:
#line 1086 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::Longboat; }
#line 5333 "grammar.gen.tab.cpp"
    break;

  case 439:
#line 1087 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::TradeCog; }
#line 5339 "grammar.gen.tab.cpp"
    break;

  case 440:
#line 1088 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::TransportShip; }
#line 5345 "grammar.gen.tab.cpp"
    break;

  case 441:
#line 1089 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::TurtleShip; }
#line 5351 "grammar.gen.tab.cpp"
    break;

  case 442:
#line 1090 "grammar.gen.ypp"
                   { yylhs.value.as < Unit > () = Unit::WarGalley; }
#line 5357 "grammar.gen.tab.cpp"
    break;

  case 443:
#line 1091 "grammar.gen.ypp"
                   { yylhs.value.as < Unit > () = Unit::TradeCart; }
#line 5363 "grammar.gen.tab.cpp"
    break;

  case 444:
#line 1092 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::Missionary; }
#line 5369 "grammar.gen.tab.cpp"
    break;

  case 445:
#line 1093 "grammar.gen.ypp"
              { yylhs.value.as < Unit > () = Unit::Monk; }
#line 5375 "grammar.gen.tab.cpp"
    break;

  case 446:
#line 1094 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::BatteringRam; }
#line 5381 "grammar.gen.tab.cpp"
    break;

  case 447:
#line 1095 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::BombardCannon; }
#line 5387 "grammar.gen.tab.cpp"
    break;

  case 448:
#line 1096 "grammar.gen.ypp"
                   { yylhs.value.as < Unit > () = Unit::CappedRam; }
#line 5393 "grammar.gen.tab.cpp"
    break;

  case 449:
#line 1097 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::HeavyScorpion; }
#line 5399 "grammar.gen.tab.cpp"
    break;

  case 450:
#line 1098 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::Mangonel; }
#line 5405 "grammar.gen.tab.cpp"
    break;

  case 451:
#line 1099 "grammar.gen.ypp"
                { yylhs.value.as < Unit > () = Unit::Onager; }
#line 5411 "grammar.gen.tab.cpp"
    break;

  case 452:
#line 1100 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::Scorpion; }
#line 5417 "grammar.gen.tab.cpp"
    break;

  case 453:
#line 1101 "grammar.gen.ypp"
                     { yylhs.value.as < Unit > () = Unit::SiegeOnager; }
#line 5423 "grammar.gen.tab.cpp"
    break;

  case 454:
#line 1102 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::SiegeRam; }
#line 5429 "grammar.gen.tab.cpp"
    break;

  case 455:
#line 1103 "grammar.gen.ypp"
               { yylhs.value.as < Unit > () = Unit::Camel; }
#line 5435 "grammar.gen.tab.cpp"
    break;

  case 456:
#line 1104 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::Cavalier; }
#line 5441 "grammar.gen.tab.cpp"
    break;

  case 457:
#line 1105 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::HeavyCamel; }
#line 5447 "grammar.gen.tab.cpp"
    break;

  case 458:
#line 1106 "grammar.gen.ypp"
                { yylhs.value.as < Unit > () = Unit::Hussar; }
#line 5453 "grammar.gen.tab.cpp"
    break;

  case 459:
#line 1107 "grammar.gen.ypp"
                { yylhs.value.as < Unit > () = Unit::Knight; }
#line 5459 "grammar.gen.tab.cpp"
    break;

  case 460:
#line 1108 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::LightCavalry; }
#line 5465 "grammar.gen.tab.cpp"
    break;

  case 461:
#line 1109 "grammar.gen.ypp"
                 { yylhs.value.as < Unit > () = Unit::Paladin; }
#line 5471 "grammar.gen.tab.cpp"
    break;

  case 462:
#line 1110 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::ScoutCavalry; }
#line 5477 "grammar.gen.tab.cpp"
    break;

  case 463:
#line 1111 "grammar.gen.ypp"
                  { yylhs.value.as < Unit > () = Unit::Villager; }
#line 5483 "grammar.gen.tab.cpp"
    break;

  case 464:
#line 1112 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::ArcherLine; }
#line 5489 "grammar.gen.tab.cpp"
    break;

  case 465:
#line 1113 "grammar.gen.ypp"
                           { yylhs.value.as < Unit > () = Unit::CavalryArcherLine; }
#line 5495 "grammar.gen.tab.cpp"
    break;

  case 466:
#line 1114 "grammar.gen.ypp"
                        { yylhs.value.as < Unit > () = Unit::SkirmisherLine; }
#line 5501 "grammar.gen.tab.cpp"
    break;

  case 467:
#line 1115 "grammar.gen.ypp"
                          { yylhs.value.as < Unit > () = Unit::EagleWarriorLine; }
#line 5507 "grammar.gen.tab.cpp"
    break;

  case 468:
#line 1116 "grammar.gen.ypp"
                        { yylhs.value.as < Unit > () = Unit::MilitiamanLine; }
#line 5513 "grammar.gen.tab.cpp"
    break;

  case 469:
#line 1117 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::SpearmanLine; }
#line 5519 "grammar.gen.tab.cpp"
    break;

  case 470:
#line 1118 "grammar.gen.ypp"
                     { yylhs.value.as < Unit > () = Unit::BerserkLine; }
#line 5525 "grammar.gen.tab.cpp"
    break;

  case 471:
#line 1119 "grammar.gen.ypp"
                        { yylhs.value.as < Unit > () = Unit::CataphractLine; }
#line 5531 "grammar.gen.tab.cpp"
    break;

  case 472:
#line 1120 "grammar.gen.ypp"
                     { yylhs.value.as < Unit > () = Unit::ChuKoNuLine; }
#line 5537 "grammar.gen.tab.cpp"
    break;

  case 473:
#line 1121 "grammar.gen.ypp"
                          { yylhs.value.as < Unit > () = Unit::ConquistadorLine; }
#line 5543 "grammar.gen.tab.cpp"
    break;

  case 474:
#line 1122 "grammar.gen.ypp"
                     { yylhs.value.as < Unit > () = Unit::HuskarlLine; }
#line 5549 "grammar.gen.tab.cpp"
    break;

  case 475:
#line 1123 "grammar.gen.ypp"
                           { yylhs.value.as < Unit > () = Unit::JaguarWarriorLine; }
#line 5555 "grammar.gen.tab.cpp"
    break;

  case 476:
#line 1124 "grammar.gen.ypp"
                       { yylhs.value.as < Unit > () = Unit::JanissaryLine; }
#line 5561 "grammar.gen.tab.cpp"
    break;

  case 477:
#line 1125 "grammar.gen.ypp"
                        { yylhs.value.as < Unit > () = Unit::LongbowmanLine; }
#line 5567 "grammar.gen.tab.cpp"
    break;

  case 478:
#line 1126 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::MamelukeLine; }
#line 5573 "grammar.gen.tab.cpp"
    break;

  case 479:
#line 1127 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::MangudaiLine; }
#line 5579 "grammar.gen.tab.cpp"
    break;

  case 480:
#line 1128 "grammar.gen.ypp"
                          { yylhs.value.as < Unit > () = Unit::PlumedArcherLine; }
#line 5585 "grammar.gen.tab.cpp"
    break;

  case 481:
#line 1129 "grammar.gen.ypp"
                     { yylhs.value.as < Unit > () = Unit::SamuraiLine; }
#line 5591 "grammar.gen.tab.cpp"
    break;

  case 482:
#line 1130 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::TarkanLine; }
#line 5597 "grammar.gen.tab.cpp"
    break;

  case 483:
#line 1131 "grammar.gen.ypp"
                            { yylhs.value.as < Unit > () = Unit::TeutonicKnightLine; }
#line 5603 "grammar.gen.tab.cpp"
    break;

  case 484:
#line 1132 "grammar.gen.ypp"
                            { yylhs.value.as < Unit > () = Unit::ThrowingAxemanLine; }
#line 5609 "grammar.gen.tab.cpp"
    break;

  case 485:
#line 1133 "grammar.gen.ypp"
                         { yylhs.value.as < Unit > () = Unit::WarElephantLine; }
#line 5615 "grammar.gen.tab.cpp"
    break;

  case 486:
#line 1134 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::WarWagonLine; }
#line 5621 "grammar.gen.tab.cpp"
    break;

  case 487:
#line 1135 "grammar.gen.ypp"
                        { yylhs.value.as < Unit > () = Unit::WoadRaiderLine; }
#line 5627 "grammar.gen.tab.cpp"
    break;

  case 488:
#line 1136 "grammar.gen.ypp"
                           { yylhs.value.as < Unit > () = Unit::CannonGalleonLine; }
#line 5633 "grammar.gen.tab.cpp"
    break;

  case 489:
#line 1137 "grammar.gen.ypp"
                            { yylhs.value.as < Unit > () = Unit::DemolitionShipLine; }
#line 5639 "grammar.gen.tab.cpp"
    break;

  case 490:
#line 1138 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::FireShipLine; }
#line 5645 "grammar.gen.tab.cpp"
    break;

  case 491:
#line 1139 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::GalleyLine; }
#line 5651 "grammar.gen.tab.cpp"
    break;

  case 492:
#line 1140 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::LongboatLine; }
#line 5657 "grammar.gen.tab.cpp"
    break;

  case 493:
#line 1141 "grammar.gen.ypp"
                        { yylhs.value.as < Unit > () = Unit::TurtleShipLine; }
#line 5663 "grammar.gen.tab.cpp"
    break;

  case 494:
#line 1142 "grammar.gen.ypp"
                          { yylhs.value.as < Unit > () = Unit::BatteringRamLine; }
#line 5669 "grammar.gen.tab.cpp"
    break;

  case 495:
#line 1143 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::MangonelLine; }
#line 5675 "grammar.gen.tab.cpp"
    break;

  case 496:
#line 1144 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::ScorpionLine; }
#line 5681 "grammar.gen.tab.cpp"
    break;

  case 497:
#line 1145 "grammar.gen.ypp"
                   { yylhs.value.as < Unit > () = Unit::CamelLine; }
#line 5687 "grammar.gen.tab.cpp"
    break;

  case 498:
#line 1146 "grammar.gen.ypp"
                    { yylhs.value.as < Unit > () = Unit::KnightLine; }
#line 5693 "grammar.gen.tab.cpp"
    break;

  case 499:
#line 1147 "grammar.gen.ypp"
                          { yylhs.value.as < Unit > () = Unit::ScoutCavalryLine; }
#line 5699 "grammar.gen.tab.cpp"
    break;

  case 500:
#line 1148 "grammar.gen.ypp"
                           { yylhs.value.as < Unit > () = Unit::MyEliteUniqueUnit; }
#line 5705 "grammar.gen.tab.cpp"
    break;

  case 501:
#line 1149 "grammar.gen.ypp"
                      { yylhs.value.as < Unit > () = Unit::MyUniqueUnit; }
#line 5711 "grammar.gen.tab.cpp"
    break;

  case 502:
#line 1150 "grammar.gen.ypp"
                          { yylhs.value.as < Unit > () = Unit::MyUniqueUnitLine; }
#line 5717 "grammar.gen.tab.cpp"
    break;

  case 503:
#line 1153 "grammar.gen.ypp"
                                  { yylhs.value.as < VictoryConditionName > () = VictoryConditionName::Standard; }
#line 5723 "grammar.gen.tab.cpp"
    break;

  case 504:
#line 1154 "grammar.gen.ypp"
                                  { yylhs.value.as < VictoryConditionName > () = VictoryConditionName::Conquest; }
#line 5729 "grammar.gen.tab.cpp"
    break;

  case 505:
#line 1155 "grammar.gen.ypp"
                                   { yylhs.value.as < VictoryConditionName > () = VictoryConditionName::TimeLimit; }
#line 5735 "grammar.gen.tab.cpp"
    break;

  case 506:
#line 1156 "grammar.gen.ypp"
                               { yylhs.value.as < VictoryConditionName > () = VictoryConditionName::Score; }
#line 5741 "grammar.gen.tab.cpp"
    break;

  case 507:
#line 1157 "grammar.gen.ypp"
                                { yylhs.value.as < VictoryConditionName > () = VictoryConditionName::Custom; }
#line 5747 "grammar.gen.tab.cpp"
    break;

  case 508:
#line 1160 "grammar.gen.ypp"
                           { yylhs.value.as < WallType > () = WallType::FortifiedWall; }
#line 5753 "grammar.gen.tab.cpp"
    break;

  case 509:
#line 1161 "grammar.gen.ypp"
                          { yylhs.value.as < WallType > () = WallType::PalisadeWall; }
#line 5759 "grammar.gen.tab.cpp"
    break;

  case 510:
#line 1162 "grammar.gen.ypp"
                       { yylhs.value.as < WallType > () = WallType::StoneWall; }
#line 5765 "grammar.gen.tab.cpp"
    break;

  case 511:
#line 1163 "grammar.gen.ypp"
                           { yylhs.value.as < WallType > () = WallType::StoneWallLine; }
#line 5771 "grammar.gen.tab.cpp"
    break;

  case 512:
#line 1167 "grammar.gen.ypp"
                                   { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 5777 "grammar.gen.tab.cpp"
    break;

  case 513:
#line 1170 "grammar.gen.ypp"
                                             { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < PlayerNumberType > (), yystack_[0].value.as < int > ()); }
#line 5783 "grammar.gen.tab.cpp"
    break;

  case 514:
#line 1173 "grammar.gen.ypp"
              { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[0].value.as < ActionType > ()); }
#line 5789 "grammar.gen.tab.cpp"
    break;

  case 515:
#line 1176 "grammar.gen.ypp"
                   { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < Building > ()); }
#line 5795 "grammar.gen.tab.cpp"
    break;

  case 516:
#line 1179 "grammar.gen.ypp"
                          { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < Building > ()); }
#line 5801 "grammar.gen.tab.cpp"
    break;

  case 517:
#line 1182 "grammar.gen.ypp"
                     { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 5807 "grammar.gen.tab.cpp"
    break;

  case 518:
#line 1185 "grammar.gen.ypp"
                              { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < WallType > ()); }
#line 5813 "grammar.gen.tab.cpp"
    break;

  case 519:
#line 1188 "grammar.gen.ypp"
                           { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < Commodity > ()); }
#line 5819 "grammar.gen.tab.cpp"
    break;

  case 520:
#line 1191 "grammar.gen.ypp"
                                   { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < Commodity > (), yystack_[0].value.as < int > ()); }
#line 5825 "grammar.gen.tab.cpp"
    break;

  case 521:
#line 1194 "grammar.gen.ypp"
                     { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < std::string > ()); }
#line 5831 "grammar.gen.tab.cpp"
    break;

  case 522:
#line 1197 "grammar.gen.ypp"
                           { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < std::string > ()); }
#line 5837 "grammar.gen.tab.cpp"
    break;

  case 523:
#line 1200 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 5843 "grammar.gen.tab.cpp"
    break;

  case 524:
#line 1203 "grammar.gen.ypp"
                                      { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 5849 "grammar.gen.tab.cpp"
    break;

  case 525:
#line 1206 "grammar.gen.ypp"
                     { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < std::string > ()); }
#line 5855 "grammar.gen.tab.cpp"
    break;

  case 526:
#line 1209 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 5861 "grammar.gen.tab.cpp"
    break;

  case 527:
#line 1212 "grammar.gen.ypp"
                                      { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 5867 "grammar.gen.tab.cpp"
    break;

  case 528:
#line 1215 "grammar.gen.ypp"
                        { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < std::string > ()); }
#line 5873 "grammar.gen.tab.cpp"
    break;

  case 529:
#line 1218 "grammar.gen.ypp"
                               { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 5879 "grammar.gen.tab.cpp"
    break;

  case 530:
#line 1221 "grammar.gen.ypp"
                                         { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 5885 "grammar.gen.tab.cpp"
    break;

  case 531:
#line 1224 "grammar.gen.ypp"
                         { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < std::string > ()); }
#line 5891 "grammar.gen.tab.cpp"
    break;

  case 532:
#line 1227 "grammar.gen.ypp"
                                { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 5897 "grammar.gen.tab.cpp"
    break;

  case 533:
#line 1230 "grammar.gen.ypp"
                                          { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 5903 "grammar.gen.tab.cpp"
    break;

  case 534:
#line 1233 "grammar.gen.ypp"
                                         { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < PlayerNumberType > (), yystack_[0].value.as < std::string > ()); }
#line 5909 "grammar.gen.tab.cpp"
    break;

  case 535:
#line 1236 "grammar.gen.ypp"
                                                { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < PlayerNumberType > (), yystack_[0].value.as < int > ()); }
#line 5915 "grammar.gen.tab.cpp"
    break;

  case 536:
#line 1239 "grammar.gen.ypp"
                                                          { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[3].value.as < ActionType > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 5921 "grammar.gen.tab.cpp"
    break;

  case 537:
#line 1242 "grammar.gen.ypp"
                     { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 5927 "grammar.gen.tab.cpp"
    break;

  case 538:
#line 1245 "grammar.gen.ypp"
                                                  { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < PlayerNumberType > (), yystack_[0].value.as < Commodity > ()); }
#line 5933 "grammar.gen.tab.cpp"
    break;

  case 539:
#line 1248 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < Building > ()); }
#line 5939 "grammar.gen.tab.cpp"
    break;

  case 540:
#line 1251 "grammar.gen.ypp"
                    { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < Unit > ()); }
#line 5945 "grammar.gen.tab.cpp"
    break;

  case 541:
#line 1254 "grammar.gen.ypp"
                { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[0].value.as < ActionType > ()); }
#line 5951 "grammar.gen.tab.cpp"
    break;

  case 542:
#line 1257 "grammar.gen.ypp"
                        { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 5957 "grammar.gen.tab.cpp"
    break;

  case 543:
#line 1260 "grammar.gen.ypp"
              { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[0].value.as < ActionType > ()); }
#line 5963 "grammar.gen.tab.cpp"
    break;

  case 544:
#line 1263 "grammar.gen.ypp"
                              { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 5969 "grammar.gen.tab.cpp"
    break;

  case 545:
#line 1266 "grammar.gen.ypp"
                               { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 5975 "grammar.gen.tab.cpp"
    break;

  case 546:
#line 1269 "grammar.gen.ypp"
                                { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 5981 "grammar.gen.tab.cpp"
    break;

  case 547:
#line 1272 "grammar.gen.ypp"
               { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < std::string > ()); }
#line 5987 "grammar.gen.tab.cpp"
    break;

  case 548:
#line 1275 "grammar.gen.ypp"
                    { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 5993 "grammar.gen.tab.cpp"
    break;

  case 549:
#line 1278 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < Commodity > ()); }
#line 5999 "grammar.gen.tab.cpp"
    break;

  case 550:
#line 1281 "grammar.gen.ypp"
                 { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < Age > ()); }
#line 6005 "grammar.gen.tab.cpp"
    break;

  case 551:
#line 1283 "grammar.gen.ypp"
                             { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < ResearchItem > ()); }
#line 6011 "grammar.gen.tab.cpp"
    break;

  case 552:
#line 1286 "grammar.gen.ypp"
           { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[0].value.as < ActionType > ()); }
#line 6017 "grammar.gen.tab.cpp"
    break;

  case 553:
#line 1289 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < Commodity > ()); }
#line 6023 "grammar.gen.tab.cpp"
    break;

  case 554:
#line 1292 "grammar.gen.ypp"
                                                      { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < DifficultyParameter > (), yystack_[0].value.as < int > ()); }
#line 6029 "grammar.gen.tab.cpp"
    break;

  case 555:
#line 1295 "grammar.gen.ypp"
                       { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 6035 "grammar.gen.tab.cpp"
    break;

  case 556:
#line 1298 "grammar.gen.ypp"
                                         { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < Commodity > (), yystack_[0].value.as < int > ()); }
#line 6041 "grammar.gen.tab.cpp"
    break;

  case 557:
#line 1301 "grammar.gen.ypp"
                          { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 6047 "grammar.gen.tab.cpp"
    break;

  case 558:
#line 1304 "grammar.gen.ypp"
                                { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 6053 "grammar.gen.tab.cpp"
    break;

  case 559:
#line 1307 "grammar.gen.ypp"
                     { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 6059 "grammar.gen.tab.cpp"
    break;

  case 560:
#line 1310 "grammar.gen.ypp"
                                                { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < PlayerNumberType > (), yystack_[0].value.as < DiplomaticStance > ()); }
#line 6065 "grammar.gen.tab.cpp"
    break;

  case 561:
#line 1313 "grammar.gen.ypp"
                                                  { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < StrategicNumberName > (), yystack_[0].value.as < int > ()); }
#line 6071 "grammar.gen.tab.cpp"
    break;

  case 562:
#line 1316 "grammar.gen.ypp"
        { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[0].value.as < ActionType > ()); }
#line 6077 "grammar.gen.tab.cpp"
    break;

  case 563:
#line 1319 "grammar.gen.ypp"
                 { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < int > ()); }
#line 6083 "grammar.gen.tab.cpp"
    break;

  case 564:
#line 1322 "grammar.gen.ypp"
                                  { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[2].value.as < ActionType > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 6089 "grammar.gen.tab.cpp"
    break;

  case 565:
#line 1325 "grammar.gen.ypp"
               { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[1].value.as < ActionType > (), yystack_[0].value.as < Unit > ()); }
#line 6095 "grammar.gen.tab.cpp"
    break;

  case 566:
#line 1328 "grammar.gen.ypp"
                                                      { yylhs.value.as < std::shared_ptr<ai::Action> > () = driver.createAction(yystack_[3].value.as < ActionType > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < Commodity > (), yystack_[0].value.as < int > ()); }
#line 6101 "grammar.gen.tab.cpp"
    break;

  case 567:
#line 1332 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6107 "grammar.gen.tab.cpp"
    break;

  case 568:
#line 1333 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6113 "grammar.gen.tab.cpp"
    break;

  case 569:
#line 1334 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6119 "grammar.gen.tab.cpp"
    break;

  case 570:
#line 1335 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6125 "grammar.gen.tab.cpp"
    break;

  case 571:
#line 1336 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6131 "grammar.gen.tab.cpp"
    break;

  case 572:
#line 1337 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6137 "grammar.gen.tab.cpp"
    break;

  case 573:
#line 1338 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6143 "grammar.gen.tab.cpp"
    break;

  case 574:
#line 1339 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6149 "grammar.gen.tab.cpp"
    break;

  case 575:
#line 1340 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6155 "grammar.gen.tab.cpp"
    break;

  case 576:
#line 1341 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6161 "grammar.gen.tab.cpp"
    break;

  case 577:
#line 1342 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6167 "grammar.gen.tab.cpp"
    break;

  case 578:
#line 1343 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6173 "grammar.gen.tab.cpp"
    break;

  case 579:
#line 1344 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6179 "grammar.gen.tab.cpp"
    break;

  case 580:
#line 1345 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6185 "grammar.gen.tab.cpp"
    break;

  case 581:
#line 1346 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6191 "grammar.gen.tab.cpp"
    break;

  case 582:
#line 1347 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6197 "grammar.gen.tab.cpp"
    break;

  case 583:
#line 1348 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6203 "grammar.gen.tab.cpp"
    break;

  case 584:
#line 1349 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6209 "grammar.gen.tab.cpp"
    break;

  case 585:
#line 1350 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6215 "grammar.gen.tab.cpp"
    break;

  case 586:
#line 1351 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6221 "grammar.gen.tab.cpp"
    break;

  case 587:
#line 1352 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6227 "grammar.gen.tab.cpp"
    break;

  case 588:
#line 1353 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6233 "grammar.gen.tab.cpp"
    break;

  case 589:
#line 1354 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6239 "grammar.gen.tab.cpp"
    break;

  case 590:
#line 1355 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6245 "grammar.gen.tab.cpp"
    break;

  case 591:
#line 1356 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6251 "grammar.gen.tab.cpp"
    break;

  case 592:
#line 1357 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6257 "grammar.gen.tab.cpp"
    break;

  case 593:
#line 1358 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6263 "grammar.gen.tab.cpp"
    break;

  case 594:
#line 1359 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6269 "grammar.gen.tab.cpp"
    break;

  case 595:
#line 1360 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6275 "grammar.gen.tab.cpp"
    break;

  case 596:
#line 1361 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6281 "grammar.gen.tab.cpp"
    break;

  case 597:
#line 1362 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6287 "grammar.gen.tab.cpp"
    break;

  case 598:
#line 1363 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6293 "grammar.gen.tab.cpp"
    break;

  case 599:
#line 1364 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6299 "grammar.gen.tab.cpp"
    break;

  case 600:
#line 1365 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6305 "grammar.gen.tab.cpp"
    break;

  case 601:
#line 1366 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6311 "grammar.gen.tab.cpp"
    break;

  case 602:
#line 1367 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6317 "grammar.gen.tab.cpp"
    break;

  case 603:
#line 1368 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6323 "grammar.gen.tab.cpp"
    break;

  case 604:
#line 1369 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6329 "grammar.gen.tab.cpp"
    break;

  case 605:
#line 1370 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6335 "grammar.gen.tab.cpp"
    break;

  case 606:
#line 1371 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6341 "grammar.gen.tab.cpp"
    break;

  case 607:
#line 1372 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6347 "grammar.gen.tab.cpp"
    break;

  case 608:
#line 1373 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6353 "grammar.gen.tab.cpp"
    break;

  case 609:
#line 1374 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6359 "grammar.gen.tab.cpp"
    break;

  case 610:
#line 1375 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6365 "grammar.gen.tab.cpp"
    break;

  case 611:
#line 1376 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6371 "grammar.gen.tab.cpp"
    break;

  case 612:
#line 1377 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6377 "grammar.gen.tab.cpp"
    break;

  case 613:
#line 1378 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6383 "grammar.gen.tab.cpp"
    break;

  case 614:
#line 1379 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6389 "grammar.gen.tab.cpp"
    break;

  case 615:
#line 1380 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6395 "grammar.gen.tab.cpp"
    break;

  case 616:
#line 1381 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6401 "grammar.gen.tab.cpp"
    break;

  case 617:
#line 1382 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6407 "grammar.gen.tab.cpp"
    break;

  case 618:
#line 1383 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6413 "grammar.gen.tab.cpp"
    break;

  case 619:
#line 1384 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6419 "grammar.gen.tab.cpp"
    break;

  case 620:
#line 1385 "grammar.gen.ypp"
    { yylhs.value.as < std::shared_ptr<ai::Action> > () = yystack_[0].value.as < std::shared_ptr<ai::Action> > (); }
#line 6425 "grammar.gen.tab.cpp"
    break;

  case 621:
#line 1389 "grammar.gen.ypp"
            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 6431 "grammar.gen.tab.cpp"
    break;

  case 622:
#line 1392 "grammar.gen.ypp"
             { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 6437 "grammar.gen.tab.cpp"
    break;

  case 623:
#line 1395 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6443 "grammar.gen.tab.cpp"
    break;

  case 624:
#line 1398 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6449 "grammar.gen.tab.cpp"
    break;

  case 625:
#line 1401 "grammar.gen.ypp"
                               { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Building > ()); }
#line 6455 "grammar.gen.tab.cpp"
    break;

  case 626:
#line 1404 "grammar.gen.ypp"
                               { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6461 "grammar.gen.tab.cpp"
    break;

  case 627:
#line 1407 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6467 "grammar.gen.tab.cpp"
    break;

  case 628:
#line 1410 "grammar.gen.ypp"
                                            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < Building > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6473 "grammar.gen.tab.cpp"
    break;

  case 629:
#line 1413 "grammar.gen.ypp"
                                                 { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < Building > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6479 "grammar.gen.tab.cpp"
    break;

  case 630:
#line 1416 "grammar.gen.ypp"
                               { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Building > ()); }
#line 6485 "grammar.gen.tab.cpp"
    break;

  case 631:
#line 1419 "grammar.gen.ypp"
                                          { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < int > (), yystack_[0].value.as < WallType > ()); }
#line 6491 "grammar.gen.tab.cpp"
    break;

  case 632:
#line 1422 "grammar.gen.ypp"
                                   { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < ResearchItem > ()); }
#line 6497 "grammar.gen.tab.cpp"
    break;

  case 633:
#line 1425 "grammar.gen.ypp"
                       { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Unit > ()); }
#line 6503 "grammar.gen.tab.cpp"
    break;

  case 634:
#line 1428 "grammar.gen.ypp"
                      { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Building > ()); }
#line 6509 "grammar.gen.tab.cpp"
    break;

  case 635:
#line 1431 "grammar.gen.ypp"
                        { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < int > ()); }
#line 6515 "grammar.gen.tab.cpp"
    break;

  case 636:
#line 1434 "grammar.gen.ypp"
                                  { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < int > ()); }
#line 6521 "grammar.gen.tab.cpp"
    break;

  case 637:
#line 1437 "grammar.gen.ypp"
                                 { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < int > (), yystack_[0].value.as < WallType > ()); }
#line 6527 "grammar.gen.tab.cpp"
    break;

  case 638:
#line 1440 "grammar.gen.ypp"
                                           { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < int > (), yystack_[0].value.as < WallType > ()); }
#line 6533 "grammar.gen.tab.cpp"
    break;

  case 639:
#line 1443 "grammar.gen.ypp"
                                { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Building > ()); }
#line 6539 "grammar.gen.tab.cpp"
    break;

  case 640:
#line 1446 "grammar.gen.ypp"
                              { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Commodity > ()); }
#line 6545 "grammar.gen.tab.cpp"
    break;

  case 641:
#line 1449 "grammar.gen.ypp"
                             { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < ResearchItem > ()); }
#line 6551 "grammar.gen.tab.cpp"
    break;

  case 642:
#line 1450 "grammar.gen.ypp"
                      { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Age > ()); }
#line 6557 "grammar.gen.tab.cpp"
    break;

  case 643:
#line 1453 "grammar.gen.ypp"
                                       { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < ResearchItem > ()); }
#line 6563 "grammar.gen.tab.cpp"
    break;

  case 644:
#line 1454 "grammar.gen.ypp"
                                { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Age > ()); }
#line 6569 "grammar.gen.tab.cpp"
    break;

  case 645:
#line 1457 "grammar.gen.ypp"
                               { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Commodity > ()); }
#line 6575 "grammar.gen.tab.cpp"
    break;

  case 646:
#line 1460 "grammar.gen.ypp"
           { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 6581 "grammar.gen.tab.cpp"
    break;

  case 647:
#line 1463 "grammar.gen.ypp"
                     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 6587 "grammar.gen.tab.cpp"
    break;

  case 648:
#line 1466 "grammar.gen.ypp"
                  { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Unit > ()); }
#line 6593 "grammar.gen.tab.cpp"
    break;

  case 649:
#line 1469 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Unit > ()); }
#line 6599 "grammar.gen.tab.cpp"
    break;

  case 650:
#line 1472 "grammar.gen.ypp"
                                                         { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6605 "grammar.gen.tab.cpp"
    break;

  case 651:
#line 1475 "grammar.gen.ypp"
                                                                      { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[4].value.as < Fact > (), yystack_[3].value.as < PlayerNumberType > (), yystack_[2].value.as < Building > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6611 "grammar.gen.tab.cpp"
    break;

  case 652:
#line 1478 "grammar.gen.ypp"
                                                     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6617 "grammar.gen.tab.cpp"
    break;

  case 653:
#line 1481 "grammar.gen.ypp"
                                                              { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[4].value.as < Fact > (), yystack_[3].value.as < PlayerNumberType > (), yystack_[2].value.as < Unit > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6623 "grammar.gen.tab.cpp"
    break;

  case 654:
#line 1484 "grammar.gen.ypp"
                  { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 6629 "grammar.gen.tab.cpp"
    break;

  case 655:
#line 1487 "grammar.gen.ypp"
                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Civ > ()); }
#line 6635 "grammar.gen.tab.cpp"
    break;

  case 656:
#line 1490 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6641 "grammar.gen.tab.cpp"
    break;

  case 657:
#line 1493 "grammar.gen.ypp"
                                                { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < Commodity > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6647 "grammar.gen.tab.cpp"
    break;

  case 658:
#line 1496 "grammar.gen.ypp"
                                                 { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < Commodity > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6653 "grammar.gen.tab.cpp"
    break;

  case 659:
#line 1499 "grammar.gen.ypp"
                         { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < Age > ()); }
#line 6659 "grammar.gen.tab.cpp"
    break;

  case 660:
#line 1502 "grammar.gen.ypp"
                                { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6665 "grammar.gen.tab.cpp"
    break;

  case 661:
#line 1505 "grammar.gen.ypp"
                              { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6671 "grammar.gen.tab.cpp"
    break;

  case 662:
#line 1508 "grammar.gen.ypp"
                   { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 6677 "grammar.gen.tab.cpp"
    break;

  case 663:
#line 1511 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6683 "grammar.gen.tab.cpp"
    break;

  case 664:
#line 1514 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6689 "grammar.gen.tab.cpp"
    break;

  case 665:
#line 1517 "grammar.gen.ypp"
                                     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < DifficultyLevel > ()); }
#line 6695 "grammar.gen.tab.cpp"
    break;

  case 666:
#line 1520 "grammar.gen.ypp"
                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < int > ()); }
#line 6701 "grammar.gen.tab.cpp"
    break;

  case 667:
#line 1523 "grammar.gen.ypp"
                                               { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < Commodity > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6707 "grammar.gen.tab.cpp"
    break;

  case 668:
#line 1526 "grammar.gen.ypp"
                         { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 6713 "grammar.gen.tab.cpp"
    break;

  case 669:
#line 1529 "grammar.gen.ypp"
                        { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 6719 "grammar.gen.tab.cpp"
    break;

  case 670:
#line 1532 "grammar.gen.ypp"
                                        { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < Commodity > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6725 "grammar.gen.tab.cpp"
    break;

  case 671:
#line 1535 "grammar.gen.ypp"
                                { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 6731 "grammar.gen.tab.cpp"
    break;

  case 672:
#line 1538 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6737 "grammar.gen.tab.cpp"
    break;

  case 673:
#line 1541 "grammar.gen.ypp"
                          { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6743 "grammar.gen.tab.cpp"
    break;

  case 674:
#line 1544 "grammar.gen.ypp"
                       { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 6749 "grammar.gen.tab.cpp"
    break;

  case 675:
#line 1547 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6755 "grammar.gen.tab.cpp"
    break;

  case 676:
#line 1550 "grammar.gen.ypp"
                                 { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6761 "grammar.gen.tab.cpp"
    break;

  case 677:
#line 1553 "grammar.gen.ypp"
                               { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6767 "grammar.gen.tab.cpp"
    break;

  case 678:
#line 1556 "grammar.gen.ypp"
                        { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < MapSizeType > ()); }
#line 6773 "grammar.gen.tab.cpp"
    break;

  case 679:
#line 1559 "grammar.gen.ypp"
                        { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < MapTypeName > ()); }
#line 6779 "grammar.gen.tab.cpp"
    break;

  case 680:
#line 1562 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6785 "grammar.gen.tab.cpp"
    break;

  case 681:
#line 1565 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < PlayerNumberType > ()); }
#line 6791 "grammar.gen.tab.cpp"
    break;

  case 682:
#line 1568 "grammar.gen.ypp"
                                 { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < PlayerNumberType > ()); }
#line 6797 "grammar.gen.tab.cpp"
    break;

  case 683:
#line 1571 "grammar.gen.ypp"
                                  { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < PlayerNumberType > ()); }
#line 6803 "grammar.gen.tab.cpp"
    break;

  case 684:
#line 1574 "grammar.gen.ypp"
                                  { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < PlayerNumberType > ()); }
#line 6809 "grammar.gen.tab.cpp"
    break;

  case 685:
#line 1577 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < PlayerNumberType > ()); }
#line 6815 "grammar.gen.tab.cpp"
    break;

  case 686:
#line 1580 "grammar.gen.ypp"
                                 { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < PlayerNumberType > ()); }
#line 6821 "grammar.gen.tab.cpp"
    break;

  case 687:
#line 1583 "grammar.gen.ypp"
                                                       { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6827 "grammar.gen.tab.cpp"
    break;

  case 688:
#line 1586 "grammar.gen.ypp"
                                                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[4].value.as < Fact > (), yystack_[3].value.as < PlayerNumberType > (), yystack_[2].value.as < Building > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6833 "grammar.gen.tab.cpp"
    break;

  case 689:
#line 1589 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < PlayerNumberType > (), yystack_[0].value.as < Civ > ()); }
#line 6839 "grammar.gen.tab.cpp"
    break;

  case 690:
#line 1592 "grammar.gen.ypp"
                                                            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6845 "grammar.gen.tab.cpp"
    break;

  case 691:
#line 1595 "grammar.gen.ypp"
                                                 { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < Age > ()); }
#line 6851 "grammar.gen.tab.cpp"
    break;

  case 692:
#line 1598 "grammar.gen.ypp"
                                                        { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6857 "grammar.gen.tab.cpp"
    break;

  case 693:
#line 1601 "grammar.gen.ypp"
                                                            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6863 "grammar.gen.tab.cpp"
    break;

  case 694:
#line 1604 "grammar.gen.ypp"
                                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6869 "grammar.gen.tab.cpp"
    break;

  case 695:
#line 1607 "grammar.gen.ypp"
                                               { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6875 "grammar.gen.tab.cpp"
    break;

  case 696:
#line 1610 "grammar.gen.ypp"
                                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < PlayerNumberType > (), yystack_[0].value.as < DiplomaticStance > ()); }
#line 6881 "grammar.gen.tab.cpp"
    break;

  case 697:
#line 1613 "grammar.gen.ypp"
                                                           { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[4].value.as < Fact > (), yystack_[3].value.as < PlayerNumberType > (), yystack_[2].value.as < Commodity > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6887 "grammar.gen.tab.cpp"
    break;

  case 698:
#line 1616 "grammar.gen.ypp"
                                                                 { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[4].value.as < Fact > (), yystack_[3].value.as < PlayerNumberType > (), yystack_[2].value.as < Commodity > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6893 "grammar.gen.tab.cpp"
    break;

  case 699:
#line 1619 "grammar.gen.ypp"
                                                   { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < PlayerNumberType > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6899 "grammar.gen.tab.cpp"
    break;

  case 700:
#line 1622 "grammar.gen.ypp"
                                                            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[4].value.as < Fact > (), yystack_[3].value.as < PlayerNumberType > (), yystack_[2].value.as < Unit > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6905 "grammar.gen.tab.cpp"
    break;

  case 701:
#line 1625 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6911 "grammar.gen.tab.cpp"
    break;

  case 702:
#line 1628 "grammar.gen.ypp"
                               { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6917 "grammar.gen.tab.cpp"
    break;

  case 703:
#line 1631 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6923 "grammar.gen.tab.cpp"
    break;

  case 704:
#line 1634 "grammar.gen.ypp"
                              { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6929 "grammar.gen.tab.cpp"
    break;

  case 705:
#line 1637 "grammar.gen.ypp"
                 { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 6935 "grammar.gen.tab.cpp"
    break;

  case 706:
#line 1640 "grammar.gen.ypp"
                                   { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < ResearchItem > ()); }
#line 6941 "grammar.gen.tab.cpp"
    break;

  case 707:
#line 1643 "grammar.gen.ypp"
                                   { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < ResearchItem > ()); }
#line 6947 "grammar.gen.tab.cpp"
    break;

  case 708:
#line 1646 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Commodity > ()); }
#line 6953 "grammar.gen.tab.cpp"
    break;

  case 709:
#line 1649 "grammar.gen.ypp"
                             { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 6959 "grammar.gen.tab.cpp"
    break;

  case 710:
#line 1652 "grammar.gen.ypp"
                         { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 6965 "grammar.gen.tab.cpp"
    break;

  case 711:
#line 1655 "grammar.gen.ypp"
                              { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6971 "grammar.gen.tab.cpp"
    break;

  case 712:
#line 1658 "grammar.gen.ypp"
                                                   { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < PlayerNumberType > (), yystack_[0].value.as < DiplomaticStance > ()); }
#line 6977 "grammar.gen.tab.cpp"
    break;

  case 713:
#line 1661 "grammar.gen.ypp"
                          { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < Age > ()); }
#line 6983 "grammar.gen.tab.cpp"
    break;

  case 714:
#line 1664 "grammar.gen.ypp"
                                                  { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < StartingResourcesType > ()); }
#line 6989 "grammar.gen.tab.cpp"
    break;

  case 715:
#line 1667 "grammar.gen.ypp"
                             { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 6995 "grammar.gen.tab.cpp"
    break;

  case 716:
#line 1670 "grammar.gen.ypp"
                                                     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < StrategicNumberName > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 7001 "grammar.gen.tab.cpp"
    break;

  case 717:
#line 1673 "grammar.gen.ypp"
                                          { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < PlayerNumberType > (), yystack_[0].value.as < int > ()); }
#line 7007 "grammar.gen.tab.cpp"
    break;

  case 718:
#line 1676 "grammar.gen.ypp"
                          { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < int > ()); }
#line 7013 "grammar.gen.tab.cpp"
    break;

  case 719:
#line 1679 "grammar.gen.ypp"
                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[0].value.as < Fact > ()); }
#line 7019 "grammar.gen.tab.cpp"
    break;

  case 720:
#line 1682 "grammar.gen.ypp"
                       { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < Unit > ()); }
#line 7025 "grammar.gen.tab.cpp"
    break;

  case 721:
#line 1685 "grammar.gen.ypp"
                           { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 7031 "grammar.gen.tab.cpp"
    break;

  case 722:
#line 1688 "grammar.gen.ypp"
                                { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 7037 "grammar.gen.tab.cpp"
    break;

  case 723:
#line 1691 "grammar.gen.ypp"
                                    { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < Unit > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 7043 "grammar.gen.tab.cpp"
    break;

  case 724:
#line 1694 "grammar.gen.ypp"
                                         { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < Unit > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 7049 "grammar.gen.tab.cpp"
    break;

  case 725:
#line 1697 "grammar.gen.ypp"
                                          { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[1].value.as < Fact > (), yystack_[0].value.as < VictoryConditionName > ()); }
#line 7055 "grammar.gen.tab.cpp"
    break;

  case 726:
#line 1700 "grammar.gen.ypp"
                                                { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < int > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 7061 "grammar.gen.tab.cpp"
    break;

  case 727:
#line 1703 "grammar.gen.ypp"
                                                { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[3].value.as < Fact > (), yystack_[2].value.as < int > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 7067 "grammar.gen.tab.cpp"
    break;

  case 728:
#line 1706 "grammar.gen.ypp"
                              { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 7073 "grammar.gen.tab.cpp"
    break;

  case 729:
#line 1709 "grammar.gen.ypp"
                            { yylhs.value.as < std::shared_ptr<ai::Condition> > () = driver.createCondition(yystack_[2].value.as < Fact > (), yystack_[1].value.as < RelOp > (), yystack_[0].value.as < int > ()); }
#line 7079 "grammar.gen.tab.cpp"
    break;

  case 730:
#line 1712 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7085 "grammar.gen.tab.cpp"
    break;

  case 731:
#line 1713 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7091 "grammar.gen.tab.cpp"
    break;

  case 732:
#line 1714 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7097 "grammar.gen.tab.cpp"
    break;

  case 733:
#line 1715 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7103 "grammar.gen.tab.cpp"
    break;

  case 734:
#line 1716 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7109 "grammar.gen.tab.cpp"
    break;

  case 735:
#line 1717 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7115 "grammar.gen.tab.cpp"
    break;

  case 736:
#line 1718 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7121 "grammar.gen.tab.cpp"
    break;

  case 737:
#line 1719 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7127 "grammar.gen.tab.cpp"
    break;

  case 738:
#line 1720 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7133 "grammar.gen.tab.cpp"
    break;

  case 739:
#line 1721 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7139 "grammar.gen.tab.cpp"
    break;

  case 740:
#line 1722 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7145 "grammar.gen.tab.cpp"
    break;

  case 741:
#line 1723 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7151 "grammar.gen.tab.cpp"
    break;

  case 742:
#line 1724 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7157 "grammar.gen.tab.cpp"
    break;

  case 743:
#line 1725 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7163 "grammar.gen.tab.cpp"
    break;

  case 744:
#line 1726 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7169 "grammar.gen.tab.cpp"
    break;

  case 745:
#line 1727 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7175 "grammar.gen.tab.cpp"
    break;

  case 746:
#line 1728 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7181 "grammar.gen.tab.cpp"
    break;

  case 747:
#line 1729 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7187 "grammar.gen.tab.cpp"
    break;

  case 748:
#line 1730 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7193 "grammar.gen.tab.cpp"
    break;

  case 749:
#line 1731 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7199 "grammar.gen.tab.cpp"
    break;

  case 750:
#line 1732 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7205 "grammar.gen.tab.cpp"
    break;

  case 751:
#line 1733 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7211 "grammar.gen.tab.cpp"
    break;

  case 752:
#line 1734 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7217 "grammar.gen.tab.cpp"
    break;

  case 753:
#line 1735 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7223 "grammar.gen.tab.cpp"
    break;

  case 754:
#line 1736 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7229 "grammar.gen.tab.cpp"
    break;

  case 755:
#line 1737 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7235 "grammar.gen.tab.cpp"
    break;

  case 756:
#line 1738 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7241 "grammar.gen.tab.cpp"
    break;

  case 757:
#line 1739 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7247 "grammar.gen.tab.cpp"
    break;

  case 758:
#line 1740 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7253 "grammar.gen.tab.cpp"
    break;

  case 759:
#line 1741 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7259 "grammar.gen.tab.cpp"
    break;

  case 760:
#line 1742 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7265 "grammar.gen.tab.cpp"
    break;

  case 761:
#line 1743 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7271 "grammar.gen.tab.cpp"
    break;

  case 762:
#line 1744 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7277 "grammar.gen.tab.cpp"
    break;

  case 763:
#line 1745 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7283 "grammar.gen.tab.cpp"
    break;

  case 764:
#line 1746 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7289 "grammar.gen.tab.cpp"
    break;

  case 765:
#line 1747 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7295 "grammar.gen.tab.cpp"
    break;

  case 766:
#line 1748 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7301 "grammar.gen.tab.cpp"
    break;

  case 767:
#line 1749 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7307 "grammar.gen.tab.cpp"
    break;

  case 768:
#line 1750 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7313 "grammar.gen.tab.cpp"
    break;

  case 769:
#line 1751 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7319 "grammar.gen.tab.cpp"
    break;

  case 770:
#line 1752 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7325 "grammar.gen.tab.cpp"
    break;

  case 771:
#line 1753 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7331 "grammar.gen.tab.cpp"
    break;

  case 772:
#line 1754 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7337 "grammar.gen.tab.cpp"
    break;

  case 773:
#line 1755 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7343 "grammar.gen.tab.cpp"
    break;

  case 774:
#line 1756 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7349 "grammar.gen.tab.cpp"
    break;

  case 775:
#line 1757 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7355 "grammar.gen.tab.cpp"
    break;

  case 776:
#line 1758 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7361 "grammar.gen.tab.cpp"
    break;

  case 777:
#line 1759 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7367 "grammar.gen.tab.cpp"
    break;

  case 778:
#line 1760 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7373 "grammar.gen.tab.cpp"
    break;

  case 779:
#line 1761 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7379 "grammar.gen.tab.cpp"
    break;

  case 780:
#line 1762 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7385 "grammar.gen.tab.cpp"
    break;

  case 781:
#line 1763 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7391 "grammar.gen.tab.cpp"
    break;

  case 782:
#line 1764 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7397 "grammar.gen.tab.cpp"
    break;

  case 783:
#line 1765 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7403 "grammar.gen.tab.cpp"
    break;

  case 784:
#line 1766 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7409 "grammar.gen.tab.cpp"
    break;

  case 785:
#line 1767 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7415 "grammar.gen.tab.cpp"
    break;

  case 786:
#line 1768 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7421 "grammar.gen.tab.cpp"
    break;

  case 787:
#line 1769 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7427 "grammar.gen.tab.cpp"
    break;

  case 788:
#line 1770 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7433 "grammar.gen.tab.cpp"
    break;

  case 789:
#line 1771 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7439 "grammar.gen.tab.cpp"
    break;

  case 790:
#line 1772 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7445 "grammar.gen.tab.cpp"
    break;

  case 791:
#line 1773 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7451 "grammar.gen.tab.cpp"
    break;

  case 792:
#line 1774 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7457 "grammar.gen.tab.cpp"
    break;

  case 793:
#line 1775 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7463 "grammar.gen.tab.cpp"
    break;

  case 794:
#line 1776 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7469 "grammar.gen.tab.cpp"
    break;

  case 795:
#line 1777 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7475 "grammar.gen.tab.cpp"
    break;

  case 796:
#line 1778 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7481 "grammar.gen.tab.cpp"
    break;

  case 797:
#line 1779 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7487 "grammar.gen.tab.cpp"
    break;

  case 798:
#line 1780 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7493 "grammar.gen.tab.cpp"
    break;

  case 799:
#line 1781 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7499 "grammar.gen.tab.cpp"
    break;

  case 800:
#line 1782 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7505 "grammar.gen.tab.cpp"
    break;

  case 801:
#line 1783 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7511 "grammar.gen.tab.cpp"
    break;

  case 802:
#line 1784 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7517 "grammar.gen.tab.cpp"
    break;

  case 803:
#line 1785 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7523 "grammar.gen.tab.cpp"
    break;

  case 804:
#line 1786 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7529 "grammar.gen.tab.cpp"
    break;

  case 805:
#line 1787 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7535 "grammar.gen.tab.cpp"
    break;

  case 806:
#line 1788 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7541 "grammar.gen.tab.cpp"
    break;

  case 807:
#line 1789 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7547 "grammar.gen.tab.cpp"
    break;

  case 808:
#line 1790 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7553 "grammar.gen.tab.cpp"
    break;

  case 809:
#line 1791 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7559 "grammar.gen.tab.cpp"
    break;

  case 810:
#line 1792 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7565 "grammar.gen.tab.cpp"
    break;

  case 811:
#line 1793 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7571 "grammar.gen.tab.cpp"
    break;

  case 812:
#line 1794 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7577 "grammar.gen.tab.cpp"
    break;

  case 813:
#line 1795 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7583 "grammar.gen.tab.cpp"
    break;

  case 814:
#line 1796 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7589 "grammar.gen.tab.cpp"
    break;

  case 815:
#line 1797 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7595 "grammar.gen.tab.cpp"
    break;

  case 816:
#line 1798 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7601 "grammar.gen.tab.cpp"
    break;

  case 817:
#line 1799 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7607 "grammar.gen.tab.cpp"
    break;

  case 818:
#line 1800 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7613 "grammar.gen.tab.cpp"
    break;

  case 819:
#line 1801 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7619 "grammar.gen.tab.cpp"
    break;

  case 820:
#line 1802 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7625 "grammar.gen.tab.cpp"
    break;

  case 821:
#line 1803 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7631 "grammar.gen.tab.cpp"
    break;

  case 822:
#line 1804 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7637 "grammar.gen.tab.cpp"
    break;

  case 823:
#line 1805 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7643 "grammar.gen.tab.cpp"
    break;

  case 824:
#line 1806 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7649 "grammar.gen.tab.cpp"
    break;

  case 825:
#line 1807 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7655 "grammar.gen.tab.cpp"
    break;

  case 826:
#line 1808 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7661 "grammar.gen.tab.cpp"
    break;

  case 827:
#line 1809 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7667 "grammar.gen.tab.cpp"
    break;

  case 828:
#line 1810 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7673 "grammar.gen.tab.cpp"
    break;

  case 829:
#line 1811 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7679 "grammar.gen.tab.cpp"
    break;

  case 830:
#line 1812 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7685 "grammar.gen.tab.cpp"
    break;

  case 831:
#line 1813 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7691 "grammar.gen.tab.cpp"
    break;

  case 832:
#line 1814 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7697 "grammar.gen.tab.cpp"
    break;

  case 833:
#line 1815 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7703 "grammar.gen.tab.cpp"
    break;

  case 834:
#line 1816 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7709 "grammar.gen.tab.cpp"
    break;

  case 835:
#line 1817 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7715 "grammar.gen.tab.cpp"
    break;

  case 836:
#line 1818 "grammar.gen.ypp"
     { yylhs.value.as < std::shared_ptr<ai::Condition> > () = yystack_[0].value.as < std::shared_ptr<ai::Condition> > (); }
#line 7721 "grammar.gen.tab.cpp"
    break;


#line 7725 "grammar.gen.tab.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  ScriptParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  ScriptParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short ScriptParser::yypact_ninf_ = -657;

  const signed char ScriptParser::yytable_ninf_ = -1;

  const short
  ScriptParser::yypact_[] =
  {
       1,     3,    14,    20,     1,    75,  -657,  -657,  -657,   141,
      73,    75,    75,    75,  -206,  -206,    58,  -206,  -206,    58,
      58,    58,    80,  1202,   658,    58,    82,   109,   111,   112,
      58,    25,   821,   821,    25,  -657,  -657,   658,   658,    31,
      31,    31,    31,  -657,  -206,   212,    25,    25,  -206,  -206,
    -206,  -657,  -206,  -206,  -206,   113,    25,  -657,  -657,    25,
     117,  -657,  -206,  -206,   126,  -206,  -206,  -206,  -133,   311,
    -206,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,  -206,  -206,  -206,  -206,  -657,  1202,  1202,    25,   127,
    -657,  -206,    31,  -206,  -206,  -206,   930,    31,   130,  -657,
    -657,   658,  -206,  -206,   658,   658,  -536,   134,   135,  -206,
    -206,   142,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
     144,  -657,  -657,    75,  -657,  -657,  -657,  -657,  -657,  -657,
     154,   155,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,   156,   161,  -206,
    -206,  -657,  -514,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -514,  -514,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -206,    58,  -206,   658,   162,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -206,  -206,    40,   165,   166,
     168,   172,     6,  -657,  -206,  -206,   173,   174,   175,   176,
     177,   180,   181,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,   182,  -657,  -657,
    -657,  -657,  -657,  -206,    58,   212,  -206,  -206,  -206,  -206,
    -206,  -206,   -76,    25,    25,  -206,   658,  -657,   183,   184,
     187,   188,  -657,  -657,  -657,   189,   190,   -76,    40,  -306,
     191,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -206,   197,  -657,  -657,   198,   217,  -206,
    -206,  -657,  -657,  -657,  -657,  -657,  -657,  -206,  -206,   240,
     242,  -657,   319,   239,   144,  -657,  -657,  -657,  -657,  -657,
     244,   245,  -657,  -657,  -657,  -657,  -657,  -657,  -657,   246,
    -206,   247,  -206,  -657,   248,   249,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,   250,   251,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,   252,  -206,  -657,
     253,    40,   256,   258,   259,   260,  -657,  -657,  -657,  -657,
    -206,  -206,   261,  -206,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,   269,  -657,  -657,
    -657,   270,   272,   273,   274,  -657,  -657,   275,    31,  -657,
      58,    58,   276,   277,    25,    25,   278,   279,   281,   282,
     284,   286,   283,   288,   296,   301,   303,   302,   305,    31,
      31,    31,   306,    31,    58,   658,  -657,   307,  -657,   308,
     309,   325,   331,   326,    25,   821,  -657,    25,   -62,   337,
      25,   338,   339,   341,    31,   930,  -657,   342,   346,   658,
      31,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,   343,  -657,  -657,  -657,  -657,
    -657,   348,  -657,   370,  -657,  -657,  -657,  -657,  -657,   371,
    -657,  -657,  -657,  -657,  -657,  -657,   372,   373,  -657,   374,
    -657,  -657,  -657,  -657,  -657,   377,   380,  -657,  -657,  -657,
    -514,  -657,   381,  -657,  -657,  -657,   382,  -657,  -657,  -657,
     383,  -657,   384,  -657,  -657,   385,   386,   388,   389,  -657,
      25,  -657,  -657,  -657,   390,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,   391,  -657,   392,   393,   394,
    -657,   -76,   396,  -657,   397,  -657,    25,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,   398,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,   399,  -657,  -657
  };

  const short
  ScriptParser::yydefact_[] =
  {
       2,     0,     0,     0,     4,     0,     1,     3,     5,     0,
       0,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   646,   647,     0,     0,     0,
       0,     0,     0,   654,     0,     0,     0,     0,     0,     0,
       0,   662,     0,     0,     0,     0,     0,   668,   669,     0,
       0,   622,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   705,     0,     0,     0,     0,
     710,     0,     0,     0,     0,     0,     0,     0,     0,   719,
     621,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   730,   731,   732,   733,   734,   735,   736,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   751,   752,   753,   754,   755,   756,   757,
     758,   759,   760,   761,   762,   763,   764,   765,   766,   767,
     768,   769,   770,   771,   772,   773,   774,   775,   776,   777,
     778,   779,   780,   781,   782,   783,   784,   785,   786,   787,
     788,   789,   790,   791,   792,   793,   794,   795,   796,   797,
     798,   799,   800,   801,   802,   803,   804,   805,   806,   807,
     808,   809,   810,   811,   812,   813,   814,   815,   816,   817,
     818,   819,   820,   821,   822,   823,   824,   825,   826,   827,
     828,   829,   830,   831,   832,   833,   834,   835,   836,    12,
       0,     8,    10,     0,   113,   114,   115,   116,   117,   118,
       0,     0,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,   625,     0,     0,     0,
       0,   630,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     632,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   633,   634,   635,   636,     0,     0,   639,
      60,    61,    62,    63,   640,    16,    17,    18,    19,    20,
      21,   642,   641,   644,   643,   645,   648,   649,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,     0,     0,     0,     0,     0,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,   655,     0,     0,     0,     0,     0,
       0,     0,     0,   666,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    74,    75,    76,    77,    78,    79,   678,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,   679,     0,   681,   682,
     683,   684,   685,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   686,     0,     0,
       0,     0,   706,   707,   708,     0,     0,     0,     0,     0,
       0,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,     0,     0,   718,   720,     0,     0,     0,
       0,   503,   504,   505,   506,   507,   725,     0,     0,     0,
       0,     9,     0,     0,    13,    11,   623,   624,   626,   627,
       0,     0,   508,   509,   510,   511,   631,   637,   638,     0,
       0,     0,     0,   656,     0,     0,   659,   660,   661,   663,
     664,    64,    65,    66,    67,    68,   665,     0,     0,   671,
     672,   673,   674,   675,   676,   677,   680,     0,     0,   689,
       0,     0,     0,     0,     0,     0,    71,    72,    73,   696,
       0,     0,     0,     0,   701,   702,   703,   704,   709,   711,
     712,   713,   236,   237,   238,   714,   715,     0,   717,   721,
     722,     0,     0,     0,     0,   728,   729,     0,     0,   514,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   541,     0,   543,     0,
       0,     0,     0,     0,     0,     0,   552,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   562,     0,     0,     0,
       0,   567,   568,   569,   570,   571,   572,   573,   574,   575,
     576,   577,   578,   579,   580,   581,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   619,   620,     0,     6,    14,   628,   629,
     650,     0,   652,     0,   657,   658,   667,   670,   687,     0,
     690,   691,   692,   693,   694,   695,     0,     0,   699,     0,
     716,   723,   724,   726,   727,     0,     0,   515,   516,   517,
       0,   519,     0,   521,   522,   523,     0,   525,   528,   529,
       0,   526,     0,   531,   532,     0,     0,     0,     0,   537,
       0,   539,   540,   542,     0,   545,   546,   547,   548,   549,
     550,   551,   553,    69,    70,     0,   555,     0,     0,     0,
     559,     0,     0,   563,     0,   565,     0,    15,   651,   653,
     688,   697,   698,   700,   512,   513,   518,   520,   524,   530,
     527,   533,   534,   535,     0,   538,   544,   554,   556,   557,
     558,   560,   561,   564,     0,   536,   566
  };

  const short
  ScriptParser::yypgoto_[] =
  {
    -657,  -657,   416,  -657,   378,    11,  -657,  -533,  -657,   -27,
      -4,  -214,   -34,  -657,  -657,  -656,  -657,  -657,   -32,    69,
     -28,  -657,  -523,   -35,  -657,  -509,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,
    -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657,  -657
  };

  const short
  ScriptParser::yydefgoto_[] =
  {
      -1,     2,     3,     4,    10,    11,   121,   813,   814,   541,
     266,   584,   534,   846,  1075,   869,   609,   626,   565,   240,
     390,   885,   793,   523,   806,   826,   951,   952,   953,   954,
     955,   956,   957,   958,   959,   960,   961,   962,   963,   964,
     965,   966,   967,   968,   969,   970,   971,   972,   973,   974,
     975,   976,   977,   978,   979,   980,   981,   982,   983,   984,
     985,   986,   987,   988,   989,   990,   991,   992,   993,   994,
     995,   996,   997,   998,   999,  1000,  1001,  1002,  1003,  1004,
    1005,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229
  };

  const short
  ScriptParser::yytable_[] =
  {
     545,   880,   546,   547,   542,   544,   543,     1,   566,   567,
     568,     5,   585,   586,     6,   269,   270,   271,   827,   828,
       7,   524,   594,   232,   233,   595,   529,   234,   235,   236,
     237,   238,   239,   603,   604,   605,   606,   607,   608,   628,
     629,   630,   631,   632,   633,   634,   635,   636,   637,   638,
     639,   640,   641,   642,   643,   644,   645,   646,   647,   535,
     536,   537,   538,   539,   654,   866,   867,   868,   652,   653,
     657,   882,   883,   884,   540,   794,   796,  1073,  1074,   799,
     800,     9,   230,   272,   241,   525,   267,   268,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   526,   569,   527,   528,   593,   587,   588,   589,
     596,   590,   591,   592,   801,   802,   803,   804,   805,   599,
     655,   597,   598,   795,   600,   601,   602,   807,   808,   627,
     841,   842,   843,   844,   845,   530,   531,   532,   533,   811,
     812,    12,    13,   822,   823,   824,   825,   816,   817,   818,
     648,   649,   650,   651,   819,   833,    14,    15,   837,   838,
     656,   839,   658,   659,   660,   840,   849,   850,   851,   852,
     853,   797,   798,   854,   855,   856,   874,   875,   809,   810,
     876,   877,   878,   879,   886,    16,    17,    18,    19,    20,
     888,   889,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
     890,    39,    40,    41,    42,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,   564,    43,   895,   815,   896,  1006,  1008,  1009,  1010,
    1012,  1014,  1015,  1016,  1017,  1018,  1020,    44,    45,  1022,
      46,  1023,  1024,  1025,  1028,    47,    48,    49,    50,    51,
      52,    53,  1030,  1031,    54,  1032,  1033,  1034,  1035,  1039,
    1040,  1007,  1043,  1044,  1045,  1046,  1049,    55,  1047,    56,
    1048,  1050,    57,    58,    59,    60,    61,    62,    63,  1051,
      64,    65,    66,    67,  1052,  1054,    68,  1053,  1055,  1059,
    1063,  1064,  1065,    69,   570,   571,   572,   573,   574,   575,
     576,   577,   578,   579,   580,   581,   582,   583,  1066,  1068,
      70,    71,    72,    73,    74,  1067,   897,   898,   820,   821,
    1076,  1078,  1079,   899,  1080,  1083,   900,   901,   902,  1084,
    1087,  1088,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,  1089,  1090,  1091,  1092,  1093,   903,   904,
    1094,    96,    97,  1095,  1097,  1098,  1099,  1100,  1101,   231,
    1102,  1103,  1104,  1106,  1107,  1108,  1109,  1110,   905,  1112,
    1113,  1115,  1116,   906,   907,   908,   909,   910,   911,   912,
     913,   914,   915,   916,   917,   918,   919,   920,   921,   922,
       8,   859,  1082,     0,     0,  1111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   923,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     924,   925,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   926,   927,     0,   928,     0,   929,   930,
       0,     0,     0,     0,     0,     0,     0,   931,     0,     0,
       0,     0,   932,   933,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   619,   620,   621,   622,   623,   624,   625,
       0,    98,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    99,   100,   101,     0,   102,   103,   104,     0,     0,
       0,   105,   106,     0,     0,     0,     0,     0,     0,     0,
       0,  1096,     0,   832,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   934,     0,     0,     0,     0,     0,     0,   935,     0,
     836,     0,   830,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   870,
     871,   873,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     858,   881,     0,     0,   829,     0,   831,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   834,   835,   107,     0,   108,   109,
       0,     0,   110,   847,   848,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   936,     0,
     937,   938,   939,   940,   941,   942,   943,   944,   945,     0,
       0,     0,   946,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   857,     0,     0,   860,   861,   862,   863,   864,
     865,     0,     0,     0,   872,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   111,   112,   113,   114,   115,
     116,     0,     0,     0,     0,     0,   117,   118,     0,     0,
       0,     0,   119,   120,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   947,  1021,   948,     0,     0,   949,   950,
     535,   536,   537,   538,   539,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   540,     0,     0,     0,     0,
       0,     0,   887,     0,     0,     0,  1036,     0,   891,   892,
    1041,  1042,     0,     0,     0,     0,   893,   894,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1056,  1057,  1058,
    1062,  1060,     0,     0,     0,     0,  1037,  1038,     0,  1011,
    1069,  1013,     0,  1072,     0,     0,  1077,  1071,  1070,     0,
       0,     0,  1081,     0,  1085,     0,     0,     0,  1086,     0,
    1061,     0,     0,     0,     0,     0,     0,  1019,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1026,
    1027,     0,  1029,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   661,   662,   663,   664,   665,   666,   667,   668,
     669,   670,   671,   672,   673,   674,   675,   676,   677,   678,
     679,   680,   681,   682,   683,   684,   685,   686,   687,   688,
     689,   690,   691,   692,   693,   694,   695,   696,   697,   698,
     699,   700,   701,   702,   703,   704,   705,   706,   707,   708,
     709,   710,   711,   712,   713,   714,   715,   716,   717,   718,
     719,   720,   721,   722,   723,   724,   725,   726,   727,   728,
     729,   730,   731,   732,   733,   734,   735,   736,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,   750,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   760,   761,   762,   763,   764,   765,   766,   767,   768,
     769,   770,   771,   772,   773,   774,   775,   776,   777,   778,
     779,   780,   781,   782,   783,   784,   785,   786,   787,   788,
     789,   790,   791,   792,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389
  };

  const short
  ScriptParser::yycheck_[] =
  {
      34,   657,    37,    38,    32,    33,    33,     6,    40,    41,
      42,     8,    46,    47,     0,    19,    20,    21,   527,   528,
       0,    25,    56,    12,    13,    59,    30,   233,   234,   235,
     236,   237,   238,   166,   167,   168,   169,   170,   171,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    19,
      20,    21,    22,    23,    98,   141,   142,   143,    96,    97,
     102,   377,   378,   379,    34,   107,   111,   139,   140,   114,
     115,     6,     9,     3,    15,     3,    17,    18,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,     3,    44,     3,     3,     3,    48,    49,    50,
       3,    52,    53,    54,   660,   661,   662,   663,   664,     3,
       3,    62,    63,     3,    65,    66,    67,     3,     3,    70,
     134,   135,   136,   137,   138,   120,   121,   122,   123,     7,
       6,    10,    11,   667,   668,   669,   670,     3,     3,     3,
      91,    92,    93,    94,     3,     3,    25,    26,     3,     3,
     101,     3,   103,   104,   105,     3,     3,     3,     3,     3,
       3,   112,   113,     3,     3,     3,     3,     3,   119,   120,
       3,     3,     3,     3,     3,    54,    55,    56,    57,    58,
       3,     3,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       3,    80,    81,    82,    83,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   101,     3,   233,     3,     7,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,   116,   117,     3,
     119,     3,     3,     3,     3,   124,   125,   126,   127,   128,
     129,   130,     3,     3,   133,     3,     3,     3,     3,     3,
       3,   814,     4,     4,     3,     3,     3,   146,     4,   148,
       4,     3,   151,   152,   153,   154,   155,   156,   157,     3,
     159,   160,   161,   162,     3,     3,   165,     4,     3,     3,
       3,     3,     3,   172,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     3,     3,
     189,   190,   191,   192,   193,     4,    17,    18,   269,   270,
       3,     3,     3,    24,     3,     3,    27,    28,    29,     3,
       7,     3,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,     3,     3,     3,     3,     3,    59,    60,
       3,   240,   241,     3,     3,     3,     3,     3,     3,    11,
       4,     3,     3,     3,     3,     3,     3,     3,    79,     3,
       3,     3,     3,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
       4,   635,   945,    -1,    -1,  1081,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   144,   145,    -1,   147,    -1,   149,   150,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   158,    -1,    -1,
      -1,    -1,   163,   164,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
      -1,   360,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   370,   371,   372,    -1,   374,   375,   376,    -1,    -1,
      -1,   380,   381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1040,    -1,   568,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,   239,    -1,
     587,    -1,   566,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   643,
     644,   646,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     634,   658,    -1,    -1,   565,    -1,   567,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   585,   586,   515,    -1,   517,   518,
      -1,    -1,   521,   594,   595,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   359,    -1,
     361,   362,   363,   364,   365,   366,   367,   368,   369,    -1,
      -1,    -1,   373,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   633,    -1,    -1,   636,   637,   638,   639,   640,
     641,    -1,    -1,    -1,   645,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   654,   655,   656,   657,   658,
     659,    -1,    -1,    -1,    -1,    -1,   665,   666,    -1,    -1,
      -1,    -1,   671,   672,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   514,   861,   516,    -1,    -1,   519,   520,
      19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,   793,    -1,    -1,    -1,   898,    -1,   799,   800,
     904,   905,    -1,    -1,    -1,    -1,   807,   808,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   919,   920,   921,
     925,   923,    -1,    -1,    -1,    -1,   900,   901,    -1,   830,
     934,   832,    -1,   937,    -1,    -1,   940,   935,   935,    -1,
      -1,    -1,   944,    -1,   949,    -1,    -1,    -1,   950,    -1,
     924,    -1,    -1,    -1,    -1,    -1,    -1,   858,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   870,
     871,    -1,   873,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1060,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1086,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     562,   563,   564,   565,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
     582,   583,   584,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   608,   609,   610,   611,
     612,   613,   614,   615,   616,   617,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   627,   628,   629,   630,   631,
     632,   633,   634,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   651,
     652,   653,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358
  };

  const short
  ScriptParser::yystos_[] =
  {
       0,     6,   674,   675,   676,     8,     0,     0,   675,     6,
     677,   678,    10,    11,    25,    26,    54,    55,    56,    57,
      58,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    80,
      81,    82,    83,   101,   116,   117,   119,   124,   125,   126,
     127,   128,   129,   130,   133,   146,   148,   151,   152,   153,
     154,   155,   156,   157,   159,   160,   161,   162,   165,   172,
     189,   190,   191,   192,   193,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   240,   241,   360,   370,
     371,   372,   374,   375,   376,   380,   381,   515,   517,   518,
     521,   654,   655,   656,   657,   658,   659,   665,   666,   671,
     672,   679,   754,   755,   756,   757,   758,   759,   760,   761,
     762,   763,   764,   765,   766,   767,   768,   769,   770,   771,
     772,   773,   774,   775,   776,   777,   778,   779,   780,   781,
     782,   783,   784,   785,   786,   787,   788,   789,   790,   791,
     792,   793,   794,   795,   796,   797,   798,   799,   800,   801,
     802,   803,   804,   805,   806,   807,   808,   809,   810,   811,
     812,   813,   814,   815,   816,   817,   818,   819,   820,   821,
     822,   823,   824,   825,   826,   827,   828,   829,   830,   831,
     832,   833,   834,   835,   836,   837,   838,   839,   840,   841,
     842,   843,   844,   845,   846,   847,   848,   849,   850,   851,
     852,   853,   854,   855,   856,   857,   858,   859,   860,   861,
       9,   677,   678,   678,   233,   234,   235,   236,   237,   238,
     692,   692,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,   683,   692,   692,   683,
     683,   683,     3,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     693,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,   605,   606,   607,   608,   609,   610,
     611,   612,   613,   614,   615,   616,   617,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,   633,   634,   635,   636,   637,   638,   639,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   696,   683,     3,     3,     3,     3,   683,
     120,   121,   122,   123,   685,    19,    20,    21,    22,    23,
      34,   682,   693,   682,   693,   685,   696,   696,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   691,   691,   691,   691,   692,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   684,   685,   685,   692,   692,   692,
     692,   692,   692,     3,   685,   685,     3,   692,   692,     3,
     692,   692,   692,   166,   167,   168,   169,   170,   171,   689,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   690,   692,   691,   691,
     691,   691,   691,   691,   691,   691,   691,   691,   691,   691,
     691,   691,   691,   691,   691,   691,   691,   691,   692,   692,
     692,   692,   693,   693,   685,     3,   692,   691,   692,   692,
     692,   382,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   695,   691,     3,   696,   692,   692,   696,
     696,   660,   661,   662,   663,   664,   697,     3,     3,   692,
     692,     7,     6,   680,   681,   678,     3,     3,     3,     3,
     692,   692,   667,   668,   669,   670,   698,   698,   698,   692,
     683,   692,   696,     3,   692,   692,   682,     3,     3,     3,
       3,   134,   135,   136,   137,   138,   686,   692,   692,     3,
       3,     3,     3,     3,     3,     3,     3,   692,   683,   684,
     692,   692,   692,   692,   692,   692,   141,   142,   143,   688,
     685,   685,   692,   696,     3,     3,     3,     3,     3,     3,
     688,   682,   377,   378,   379,   694,     3,   692,     3,     3,
       3,   692,   692,   692,   692,     3,     3,    17,    18,    24,
      27,    28,    29,    59,    60,    79,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   118,   131,   132,   144,   145,   147,   149,
     150,   158,   163,   164,   232,   239,   359,   361,   362,   363,
     364,   365,   366,   367,   368,   369,   373,   514,   516,   519,
     520,   699,   700,   701,   702,   703,   704,   705,   706,   707,
     708,   709,   710,   711,   712,   713,   714,   715,   716,   717,
     718,   719,   720,   721,   722,   723,   724,   725,   726,   727,
     728,   729,   730,   731,   732,   733,   734,   735,   736,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   751,   752,   753,     7,   680,     3,     3,
       3,   692,     3,   692,     3,     3,     3,     3,     3,   692,
       3,   682,     3,     3,     3,     3,   692,   692,     3,   692,
       3,     3,     3,     3,     3,     3,   691,   683,   683,     3,
       3,   685,   685,     4,     4,     3,     3,     4,     4,     3,
       3,     3,     3,     4,     3,     3,   691,   691,   691,     3,
     691,   683,   696,     3,     3,     3,     3,     4,     3,   685,
     682,   693,   685,   139,   140,   687,     3,   685,     3,     3,
       3,   691,   695,     3,     3,   696,   691,     7,     3,     3,
       3,     3,     3,     3,     3,     3,   698,     3,     3,     3,
       3,     3,     4,     3,     3,   685,     3,     3,     3,     3,
       3,   688,     3,     3,   685,     3,     3
  };

  const short
  ScriptParser::yyr1_[] =
  {
       0,   673,   674,   674,   675,   675,   676,   677,   677,   678,
     679,   679,   679,   680,   680,   681,   682,   682,   682,   682,
     682,   682,   683,   683,   683,   683,   683,   683,   683,   683,
     683,   683,   683,   683,   683,   683,   683,   683,   683,   683,
     683,   683,   683,   683,   683,   683,   684,   684,   684,   684,
     684,   684,   684,   684,   684,   684,   684,   684,   684,   684,
     685,   685,   685,   685,   686,   686,   686,   686,   686,   687,
     687,   688,   688,   688,   689,   689,   689,   689,   689,   689,
     690,   690,   690,   690,   690,   690,   690,   690,   690,   690,
     690,   690,   690,   690,   690,   690,   691,   691,   691,   691,
     691,   691,   691,   691,   691,   691,   691,   691,   691,   691,
     691,   691,   691,   692,   692,   692,   692,   692,   692,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   693,   693,   693,   693,
     693,   693,   693,   693,   693,   693,   694,   694,   694,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   696,   697,   697,   697,   697,   697,   698,   698,
     698,   698,   699,   700,   701,   702,   703,   704,   705,   706,
     707,   708,   709,   710,   711,   712,   713,   714,   715,   716,
     717,   718,   719,   720,   721,   722,   723,   724,   725,   726,
     727,   728,   729,   730,   731,   732,   733,   734,   735,   736,
     737,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,   750,   751,   752,   753,   753,   753,
     753,   753,   753,   753,   753,   753,   753,   753,   753,   753,
     753,   753,   753,   753,   753,   753,   753,   753,   753,   753,
     753,   753,   753,   753,   753,   753,   753,   753,   753,   753,
     753,   753,   753,   753,   753,   753,   753,   753,   753,   753,
     753,   753,   753,   753,   753,   753,   753,   753,   753,   753,
     753,   754,   755,   756,   757,   758,   759,   760,   761,   762,
     763,   764,   765,   766,   767,   768,   769,   770,   771,   772,
     773,   774,   774,   775,   775,   776,   777,   778,   779,   780,
     781,   782,   783,   784,   785,   786,   787,   788,   789,   790,
     791,   792,   793,   794,   795,   796,   797,   798,   799,   800,
     801,   802,   803,   804,   805,   806,   807,   808,   809,   810,
     811,   812,   813,   814,   815,   816,   817,   818,   819,   820,
     821,   822,   823,   824,   825,   826,   827,   828,   829,   830,
     831,   832,   833,   834,   835,   836,   837,   838,   839,   840,
     841,   842,   843,   844,   845,   846,   847,   848,   849,   850,
     851,   852,   853,   854,   855,   856,   857,   858,   859,   860,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861
  };

  const signed char
  ScriptParser::yyr2_[] =
  {
       0,     2,     0,     2,     1,     2,     6,     1,     2,     3,
       2,     3,     1,     1,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     2,     2,     2,     3,     2,
       3,     2,     2,     2,     3,     2,     2,     3,     2,     2,
       3,     2,     2,     3,     3,     3,     4,     2,     3,     2,
       2,     1,     2,     1,     3,     2,     2,     2,     2,     2,
       2,     2,     1,     2,     3,     2,     3,     3,     3,     2,
       3,     3,     1,     2,     3,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     2,     3,     3,     4,     4,
       2,     3,     2,     2,     2,     2,     2,     3,     3,     2,
       2,     2,     2,     2,     2,     2,     1,     1,     2,     2,
       4,     5,     4,     5,     1,     2,     3,     4,     4,     3,
       3,     3,     1,     3,     3,     3,     2,     4,     1,     1,
       4,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       3,     2,     2,     2,     2,     2,     2,     4,     5,     3,
       4,     4,     4,     4,     4,     4,     3,     5,     5,     4,
       5,     3,     3,     3,     3,     1,     2,     2,     2,     3,
       1,     3,     3,     3,     3,     3,     4,     3,     2,     1,
       2,     3,     3,     4,     4,     2,     4,     4,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const ScriptParser::yytname_[] =
  {
  "\"end of script\"", "error", "$undefined", "Number", "String",
  "SymbolName", "OpenParen", "CloseParen", "RuleStart",
  "ConditionActionSeparator", "Not", "Or", "LoadIfDefined", "Else",
  "EndIf", "Space", "NewLine", "AcknowledgeEvent", "AcknowledgeTaunt",
  "AgeDarkAge", "AgeFeudalAge", "AgeCastleAge", "AgeImperialAge",
  "AgePostImperialAge", "AttackNow", "AttackSoldierCount",
  "AttackWarboatCount", "Build", "BuildForward", "BuildGate",
  "BuildingArcheryRange", "BuildingBarracks", "BuildingBlacksmith",
  "BuildingBombardTower", "BuildingCastle", "BuildingDock", "BuildingFarm",
  "BuildingFishTrap", "BuildingGuardTower", "BuildingHouse",
  "BuildingKeep", "BuildingLumberCamp", "BuildingMarket", "BuildingMill",
  "BuildingMiningCamp", "BuildingMonastery", "BuildingOutpost",
  "BuildingSiegeWorkshop", "BuildingStable", "BuildingTownCenter",
  "BuildingUniversity", "BuildingWatchTower", "BuildingWonder",
  "BuildingWatchTowerLine", "BuildingAvailable", "BuildingCount",
  "BuildingCountTotal", "BuildingTypeCount", "BuildingTypeCountTotal",
  "BuildWall", "BuyCommodity", "CanAffordBuilding",
  "CanAffordCompleteWall", "CanAffordResearch", "CanAffordUnit",
  "CanBuild", "CanBuildGate", "CanBuildGateWithEscrow", "CanBuildWall",
  "CanBuildWallWithEscrow", "CanBuildWithEscrow", "CanBuyCommodity",
  "CanResearch", "CanResearchWithEscrow", "CanSellCommodity", "CanSpy",
  "CanSpyWithEscrow", "CanTrain", "CanTrainWithEscrow", "CcAddResource",
  "CcPlayersBuildingCount", "CcPlayersBuildingTypeCount",
  "CcPlayersUnitCount", "CcPlayersUnitTypeCount", "ChatLocal",
  "ChatLocalToSelf", "ChatLocalUsingId", "ChatLocalUsingRange",
  "ChatToAll", "ChatToAllies", "ChatToAlliesUsingId",
  "ChatToAlliesUsingRange", "ChatToAllUsingId", "ChatToAllUsingRange",
  "ChatToEnemies", "ChatToEnemiesUsingId", "ChatToEnemiesUsingRange",
  "ChatToPlayer", "ChatToPlayerUsingId", "ChatToPlayerUsingRange",
  "ChatTrace", "CheatsEnabled", "CivBriton", "CivByzantine", "CivCeltic",
  "CivChinese", "CivFrankish", "CivGothic", "CivJapanese", "CivMongol",
  "CivPersian", "CivSaracen", "CivTeutonic", "CivTurkish", "CivViking",
  "CivMyCiv", "CivilianPopulation", "CivSelected", "ClearTributeMemory",
  "CommodityBuyingPrice", "CommodityFood", "CommodityStone",
  "CommodityWood", "CommodityGold", "CommoditySellingPrice", "CurrentAge",
  "CurrentAgeTime", "CurrentScore", "DeathMatchGame", "DefendSoldierCount",
  "DefendWarboatCount", "DeleteBuilding", "DeleteUnit", "Difficulty",
  "DifficultyLevelEasiest", "DifficultyLevelEasy",
  "DifficultyLevelModerate", "DifficultyLevelHard",
  "DifficultyLevelHardest", "DifficultyParameterAbilityToDodgeMissiles",
  "DifficultyParameterAbilityToMaintainDistance", "DiplomaticStanceAlly",
  "DiplomaticStanceNeutral", "DiplomaticStanceEnemy", "DisableSelf",
  "DisableTimer", "Doctrine", "DoNothing", "DropsiteMinDistance",
  "EnableTimer", "EnableWallPlacement", "EnemyBuildingsInTown",
  "EnemyCapturedRelics", "EscrowAmount", "EventDetected", "Falseval",
  "FoodAmount", "GameTime", "GenerateRandomNumber", "Goal", "GoldAmount",
  "HousingHeadroom", "IdleFarmCount", "Log", "LogTrace", "MapSize",
  "MapSizeTypeTiny", "MapSizeTypeSmall", "MapSizeTypeMedium",
  "MapSizeTypeNormal", "MapSizeTypeLarge", "MapSizeTypeGiant", "MapType",
  "MapTypeNameArabia", "MapTypeNameArchipelago", "MapTypeNameBaltic",
  "MapTypeNameBlackForest", "MapTypeNameCoastal", "MapTypeNameContinental",
  "MapTypeNameCraterLake", "MapTypeNameFortress", "MapTypeNameGoldRush",
  "MapTypeNameHighland", "MapTypeNameIslands", "MapTypeNameMediterranean",
  "MapTypeNameMigration", "MapTypeNameRivers", "MapTypeNameTeamIslands",
  "MapTypeNameScenarioMap", "MilitaryPopulation", "PlayerComputer",
  "PlayerHuman", "PlayerInGame", "PlayerNumber", "PlayerNumberTypeAnyAlly",
  "PlayerNumberTypeAnyComputer", "PlayerNumberTypeAnyComputerAlly",
  "PlayerNumberTypeAnyComputerEnemy", "PlayerNumberTypeAnyComputerNeutral",
  "PlayerNumberTypeAnyEnemy", "PlayerNumberTypeAnyHuman",
  "PlayerNumberTypeAnyHumanAlly", "PlayerNumberTypeAnyHumanEnemy",
  "PlayerNumberTypeAnyHumanNeutral", "PlayerNumberTypeAnyNeutral",
  "PlayerNumberTypeEveryAlly", "PlayerNumberTypeEveryComputer",
  "PlayerNumberTypeEveryEnemy", "PlayerNumberTypeEveryHuman",
  "PlayerNumberTypeEveryNeutral", "PlayerNumberTypeMyPlayerNumber",
  "PlayerResigned", "PlayersBuildingCount", "PlayersBuildingTypeCount",
  "PlayersCiv", "PlayersCivilianPopulation", "PlayersCurrentAge",
  "PlayersCurrentAgeTime", "PlayersMilitaryPopulation",
  "PlayersPopulation", "PlayersScore", "PlayersStance", "PlayersTribute",
  "PlayersTributeMemory", "PlayersUnitCount", "PlayersUnitTypeCount",
  "PlayerValid", "Population", "PopulationCap", "PopulationHeadroom",
  "RandomNumber", "RegicideGame", "ReleaseEscrow", "RelOpLessThan",
  "RelOpLessOrEqual", "RelOpGreaterThan", "RelOpGreaterOrEqual",
  "RelOpEqual", "RelOpNotEqual", "Research", "ResearchAvailable",
  "ResearchCompleted", "ResearchItemRiArbalest", "ResearchItemRiCrossbow",
  "ResearchItemRiEliteSkirmisher", "ResearchItemRiHandCannon",
  "ResearchItemRiHeavyCavalryArcher", "ResearchItemRiChampion",
  "ResearchItemRiEliteEagleWarrior", "ResearchItemRiHalberdier",
  "ResearchItemRiLongSwordsman", "ResearchItemRiManAtArms",
  "ResearchItemRiParthianTactics", "ResearchItemRiPikeman",
  "ResearchItemRiSquires", "ResearchItemRiThumbRing",
  "ResearchItemRiTracking", "ResearchItemRiTwoHandedSwordsman",
  "ResearchItemRiBlastFurnace", "ResearchItemRiBodkinArrow",
  "ResearchItemRiBracer", "ResearchItemRiChainBarding",
  "ResearchItemRiChainMail", "ResearchItemRiFletching",
  "ResearchItemRiForging", "ResearchItemRiIronCasting",
  "ResearchItemRiLeatherArcherArmor", "ResearchItemRiPaddedArcherArmor",
  "ResearchItemRiPlateBarding", "ResearchItemRiPlateMail",
  "ResearchItemRiRingArcherArmor", "ResearchItemRiScaleBarding",
  "ResearchItemRiScaleMail", "ResearchItemRiConscription",
  "ResearchItemRiHoardings", "ResearchItemRiSappers",
  "ResearchItemRiEliteBerserk", "ResearchItemRiEliteCataphract",
  "ResearchItemRiEliteChuKoNu", "ResearchItemRiEliteHuskarl",
  "ResearchItemRiEliteJanissary", "ResearchItemRiEliteLongbowman",
  "ResearchItemRiEliteMameluke", "ResearchItemRiEliteMangudai",
  "ResearchItemRiEliteSamurai", "ResearchItemRiEliteTeutonicKnight",
  "ResearchItemRiEliteThrowingAxeman", "ResearchItemRiEliteWarElephant",
  "ResearchItemRiEliteWoadRaider", "ResearchItemRiMyUniqueEliteUnit",
  "ResearchItemRiMyUniqueResearch", "ResearchItemRiCannonGalleon",
  "ResearchItemRiCareening", "ResearchItemRiDeckGuns",
  "ResearchItemRiDryDock", "ResearchItemRiEliteLongboat",
  "ResearchItemRiFastFireShip", "ResearchItemRiGalleon",
  "ResearchItemRiHeavyDemolitionShip", "ResearchItemRiShipwright",
  "ResearchItemRiWarGalley", "ResearchItemRiBowSaw",
  "ResearchItemRiDoubleBitAxe", "ResearchItemRiTwoManSaw",
  "ResearchItemRiBanking", "ResearchItemRiCaravan",
  "ResearchItemRiCartography", "ResearchItemRiCoinage",
  "ResearchItemRiGuilds", "ResearchItemRiCropRotation",
  "ResearchItemRiHeavyPlow", "ResearchItemRiHorseCollar",
  "ResearchItemRiGoldMining", "ResearchItemRiGoldShaftMining",
  "ResearchItemRiStoneMining", "ResearchItemRiStoneShaftMining",
  "ResearchItemRiAtonement", "ResearchItemRiBlockPrinting",
  "ResearchItemRiFaith", "ResearchItemRiFervor",
  "ResearchItemRiHerbalMedicine", "ResearchItemRiHeresy",
  "ResearchItemRiIllumination", "ResearchItemRiRedemption",
  "ResearchItemRiSanctity", "ResearchItemRiTheocracy",
  "ResearchItemRiBombardCannon", "ResearchItemRiCappedRam",
  "ResearchItemRiHeavyScorpion", "ResearchItemRiOnager",
  "ResearchItemRiScorpion", "ResearchItemRiSiegeOnager",
  "ResearchItemRiSiegeRam", "ResearchItemRiBloodlines",
  "ResearchItemRiCavalier", "ResearchItemRiHeavyCamel",
  "ResearchItemRiHusbandry", "ResearchItemRiHussar",
  "ResearchItemRiLightCavalry", "ResearchItemRiPaladin",
  "ResearchItemRiHandCart", "ResearchItemRiLoom",
  "ResearchItemRiTownPatrol", "ResearchItemRiTownWatch",
  "ResearchItemRiWheelBarrow", "ResearchItemRiArchitecture",
  "ResearchItemRiBallistics", "ResearchItemRiBombardTower",
  "ResearchItemRiChemistry", "ResearchItemRiFortifiedWall",
  "ResearchItemRiGuardTower", "ResearchItemRiHeatedShot",
  "ResearchItemRiKeep", "ResearchItemRiMasonry",
  "ResearchItemRiMurderHoles", "ResearchItemRiSiegeEngineers",
  "ResearchItemRiStonecutting", "ResearchItemMyUniqueUnitUpgrade",
  "ResearchItemMyUniqueResearch", "Resign", "ResourceFound",
  "SellCommodity", "SetDifficultyParameter", "SetDoctrine",
  "SetEscrowPercentage", "SetGoal", "SetSharedGoal", "SetSignal",
  "SetStance", "SetStrategicNumber", "SharedGoal", "SheepAndForageTooFar",
  "SoldierCount", "Spy", "StanceToward", "StartingAge",
  "StartingResources", "StartingResourcesTypeLowResources",
  "StartingResourcesTypeMediumResources",
  "StartingResourcesTypeHighResources", "StoneAmount", "StrategicNumber",
  "StrategicNumberNameSnPercentCivilianExplorers",
  "StrategicNumberNameSnPercentCivilianBuilders",
  "StrategicNumberNameSnPercentCivilianGatherers",
  "StrategicNumberNameSnCapCivilianExplorers",
  "StrategicNumberNameSnCapCivilianBuilders",
  "StrategicNumberNameSnCapCivilianGatherers",
  "StrategicNumberNameSnMinimumAttackGroupSize",
  "StrategicNumberNameSnTotalNumberExplorers",
  "StrategicNumberNameSnPercentEnemySightedResponse",
  "StrategicNumberNameSnEnemySightedResponseDistance",
  "StrategicNumberNameSnSentryDistance",
  "StrategicNumberNameSnRelicReturnDistance",
  "StrategicNumberNameSnMinimumDefendGroupSize",
  "StrategicNumberNameSnMaximumAttackGroupSize",
  "StrategicNumberNameSnMaximumDefendGroupSize",
  "StrategicNumberNameSnMinimumPeaceLikeLevel",
  "StrategicNumberNameSnPercentExplorationRequired",
  "StrategicNumberNameSnZeroPriorityDistance",
  "StrategicNumberNameSnMinimumCivilianExplorers",
  "StrategicNumberNameSnNumberAttackGroups",
  "StrategicNumberNameSnNumberDefendGroups",
  "StrategicNumberNameSnAttackGroupGatherSpacing",
  "StrategicNumberNameSnNumberExploreGroups",
  "StrategicNumberNameSnMinimumExploreGroupSize",
  "StrategicNumberNameSnMaximumExploreGroupSize",
  "StrategicNumberNameSnGoldDefendPriority",
  "StrategicNumberNameSnStoneDefendPriority",
  "StrategicNumberNameSnForageDefendPriority",
  "StrategicNumberNameSnRelicDefendPriority",
  "StrategicNumberNameSnTownDefendPriority",
  "StrategicNumberNameSnDefenseDistance",
  "StrategicNumberNameSnNumberBoatAttackGroups",
  "StrategicNumberNameSnMinimumBoatAttackGroupSize",
  "StrategicNumberNameSnMaximumBoatAttackGroupSize",
  "StrategicNumberNameSnNumberBoatExploreGroups",
  "StrategicNumberNameSnMinimumBoatExploreGroupSize",
  "StrategicNumberNameSnMaximumBoatExploreGroupSize",
  "StrategicNumberNameSnNumberBoatDefendGroups",
  "StrategicNumberNameSnMinimumBoatDefendGroupSize",
  "StrategicNumberNameSnMaximumBoatDefendGroupSize",
  "StrategicNumberNameSnDockDefendPriority",
  "StrategicNumberNameSnSentryDistanceVariation",
  "StrategicNumberNameSnMinimumTownSize",
  "StrategicNumberNameSnMaximumTownSize",
  "StrategicNumberNameSnGroupCommanderSelectionMethod",
  "StrategicNumberNameSnConsecutiveIdleUnitLimit",
  "StrategicNumberNameSnTargetEvaluationDistance",
  "StrategicNumberNameSnTargetEvaluationHitpoints",
  "StrategicNumberNameSnTargetEvaluationDamageCapability",
  "StrategicNumberNameSnTargetEvaluationKills",
  "StrategicNumberNameSnTargetEvaluationAllyProximity",
  "StrategicNumberNameSnTargetEvaluationRof",
  "StrategicNumberNameSnTargetEvaluationRandomness",
  "StrategicNumberNameSnCampMaxDistance",
  "StrategicNumberNameSnMillMaxDistance",
  "StrategicNumberNameSnTargetEvaluationAttackAttempts",
  "StrategicNumberNameSnTargetEvaluationRange",
  "StrategicNumberNameSnDefendOverlapDistance",
  "StrategicNumberNameSnScaleMinimumAttackGroupSize",
  "StrategicNumberNameSnScaleMaximumAttackGroupSize",
  "StrategicNumberNameSnAttackGroupSizeRandomness",
  "StrategicNumberNameSnScalingFrequency",
  "StrategicNumberNameSnMaximumGaiaAttackResponse",
  "StrategicNumberNameSnBuildFrequency",
  "StrategicNumberNameSnAttackSeparationTimeRandomness",
  "StrategicNumberNameSnAttackIntelligence",
  "StrategicNumberNameSnInitialAttackDelay",
  "StrategicNumberNameSnSaveScenarioInformation",
  "StrategicNumberNameSnSpecialAttackType1",
  "StrategicNumberNameSnSpecialAttackInfluence1",
  "StrategicNumberNameSnMinimumWaterBodySizeForDock",
  "StrategicNumberNameSnNumberBuildAttemptsBeforeSkip",
  "StrategicNumberNameSnMaxSkipsPerAttempt",
  "StrategicNumberNameSnFoodGathererPercentage",
  "StrategicNumberNameSnGoldGathererPercentage",
  "StrategicNumberNameSnStoneGathererPercentage",
  "StrategicNumberNameSnWoodGathererPercentage",
  "StrategicNumberNameSnTargetEvaluationContinent",
  "StrategicNumberNameSnTargetEvaluationSiegeWeapon",
  "StrategicNumberNameSnGroupLeaderDefenseDistance",
  "StrategicNumberNameSnInitialAttackDelayType",
  "StrategicNumberNameSnBlotExplorationMap",
  "StrategicNumberNameSnBlotSize",
  "StrategicNumberNameSnIntelligentGathering",
  "StrategicNumberNameSnTaskUngroupedSoldiers",
  "StrategicNumberNameSnTargetEvaluationBoat",
  "StrategicNumberNameSnNumberEnemyObjectsRequired",
  "StrategicNumberNameSnNumberMaxSkipCycles",
  "StrategicNumberNameSnRetaskGatherAmount",
  "StrategicNumberNameSnMaxRetaskGatherAmount",
  "StrategicNumberNameSnMaxBuildPlanGathererPercentage",
  "StrategicNumberNameSnFoodDropsiteDistance",
  "StrategicNumberNameSnWoodDropsiteDistance",
  "StrategicNumberNameSnStoneDropsiteDistance",
  "StrategicNumberNameSnGoldDropsiteDistance",
  "StrategicNumberNameSnInitialExplorationRequired",
  "StrategicNumberNameSnRandomPlacementFactor",
  "StrategicNumberNameSnRequiredForestTiles",
  "StrategicNumberNameSnAttackDiplomacyImpact",
  "StrategicNumberNameSnPercentHalfExploration",
  "StrategicNumberNameSnTargetEvaluationTimeKillRatio",
  "StrategicNumberNameSnTargetEvaluationInProgress",
  "StrategicNumberNameSnAttackWinningPlayer",
  "StrategicNumberNameSnCoopShareInformation",
  "StrategicNumberNameSnAttackWinningPlayerFactor",
  "StrategicNumberNameSnCoopShareAttacking",
  "StrategicNumberNameSnCoopShareAttackingInterval",
  "StrategicNumberNameSnPercentageExploreExterminators",
  "StrategicNumberNameSnTrackPlayerHistory",
  "StrategicNumberNameSnMinimumDropsiteBuffer",
  "StrategicNumberNameSnUseByTypeMaxGathering",
  "StrategicNumberNameSnMinimumBoarHuntGroupSize",
  "StrategicNumberNameSnMinimumAmountForTrading",
  "StrategicNumberNameSnEasiestReactionPercentage",
  "StrategicNumberNameSnEasierReactionPercentage",
  "StrategicNumberNameSnHitsBeforeAllianceChange",
  "StrategicNumberNameSnAllowCivilianDefense",
  "StrategicNumberNameSnNumberForwardBuilders",
  "StrategicNumberNameSnPercentAttackSoldiers",
  "StrategicNumberNameSnPercentAttackBoats",
  "StrategicNumberNameSnDoNotScaleForDifficultyLevel",
  "StrategicNumberNameSnGroupFormDistance",
  "StrategicNumberNameSnIgnoreAttackGroupUnderAttack",
  "StrategicNumberNameSnGatherDefenseUnits",
  "StrategicNumberNameSnMaximumWoodDropDistance",
  "StrategicNumberNameSnMaximumFoodDropDistance",
  "StrategicNumberNameSnMaximumHuntDropDistance",
  "StrategicNumberNameSnMaximumFishBoatDropDistance",
  "StrategicNumberNameSnMaximumGoldDropDistance",
  "StrategicNumberNameSnMaximumStoneDropDistance",
  "StrategicNumberNameSnGatherIdleSoldiersAtCenter",
  "StrategicNumberNameSnGarrisonRams", "Taunt", "TauntDetected",
  "TauntUsingRange", "TimerTriggered", "TownUnderAttack", "Train",
  "TributeToPlayer", "Trueval", "UnitArbalest", "UnitArcher",
  "UnitCavalryArcher", "UnitCrossbowman", "UnitEliteSkirmisher",
  "UnitHandCannoneer", "UnitHeavyCavalryArcher", "UnitSkirmisher",
  "UnitChampion", "UnitEagleWarrior", "UnitEliteEagleWarrior",
  "UnitHalberdier", "UnitLongSwordsman", "UnitManAtArms", "UnitMilitiaman",
  "UnitPikeman", "UnitSpearman", "UnitTwoHandedSwordsman", "UnitBerserk",
  "UnitCataphract", "UnitChuKoNu", "UnitConquistador", "UnitEliteBerserk",
  "UnitEliteCataphract", "UnitEliteChuKoNu", "UnitEliteConquistador",
  "UnitEliteHuskarl", "UnitEliteJaguarWarrior", "UnitEliteJanissary",
  "UnitEliteLongbowman", "UnitEliteMameluke", "UnitEliteMangudai",
  "UnitElitePlumedArcher", "UnitEliteSamurai", "UnitEliteTarkan",
  "UnitEliteTeutonicKnight", "UnitEliteThrowingAxeman",
  "UnitEliteWarElephant", "UnitEliteWarWagon", "UnitEliteWoadRaider",
  "UnitHuskarl", "UnitJaguarWarrior", "UnitJanissary", "UnitLongbowman",
  "UnitMameluke", "UnitMangudai", "UnitPetard", "UnitPlumedArcher",
  "UnitSamurai", "UnitTarkan", "UnitTeutonicKnight", "UnitThrowingAxeman",
  "UnitTrebuchet", "UnitWarElephant", "UnitWarWagon", "UnitWoadRaider",
  "UnitCannonGalleon", "UnitDemolitionShip", "UnitEliteCannonGalleon",
  "UnitEliteLongboat", "UnitEliteTurtleShip", "UnitFastFireShip",
  "UnitFireShip", "UnitFishingShip", "UnitGalleon", "UnitGalley",
  "UnitHeavyDemolitionShip", "UnitLongboat", "UnitTradeCog",
  "UnitTransportShip", "UnitTurtleShip", "UnitWarGalley", "UnitTradeCart",
  "UnitMissionary", "UnitMonk", "UnitBatteringRam", "UnitBombardCannon",
  "UnitCappedRam", "UnitHeavyScorpion", "UnitMangonel", "UnitOnager",
  "UnitScorpion", "UnitSiegeOnager", "UnitSiegeRam", "UnitCamel",
  "UnitCavalier", "UnitHeavyCamel", "UnitHussar", "UnitKnight",
  "UnitLightCavalry", "UnitPaladin", "UnitScoutCavalry", "UnitVillager",
  "UnitArcherLine", "UnitCavalryArcherLine", "UnitSkirmisherLine",
  "UnitEagleWarriorLine", "UnitMilitiamanLine", "UnitSpearmanLine",
  "UnitBerserkLine", "UnitCataphractLine", "UnitChuKoNuLine",
  "UnitConquistadorLine", "UnitHuskarlLine", "UnitJaguarWarriorLine",
  "UnitJanissaryLine", "UnitLongbowmanLine", "UnitMamelukeLine",
  "UnitMangudaiLine", "UnitPlumedArcherLine", "UnitSamuraiLine",
  "UnitTarkanLine", "UnitTeutonicKnightLine", "UnitThrowingAxemanLine",
  "UnitWarElephantLine", "UnitWarWagonLine", "UnitWoadRaiderLine",
  "UnitCannonGalleonLine", "UnitDemolitionShipLine", "UnitFireShipLine",
  "UnitGalleyLine", "UnitLongboatLine", "UnitTurtleShipLine",
  "UnitBatteringRamLine", "UnitMangonelLine", "UnitScorpionLine",
  "UnitCamelLine", "UnitKnightLine", "UnitScoutCavalryLine",
  "UnitMyEliteUniqueUnit", "UnitMyUniqueUnit", "UnitMyUniqueUnitLine",
  "UnitAvailable", "UnitCount", "UnitCountTotal", "UnitTypeCount",
  "UnitTypeCountTotal", "VictoryCondition", "VictoryConditionNameStandard",
  "VictoryConditionNameConquest", "VictoryConditionNameTimeLimit",
  "VictoryConditionNameScore", "VictoryConditionNameCustom",
  "WallCompletedPercentage", "WallInvisiblePercentage",
  "WallTypeFortifiedWall", "WallTypePalisadeWall", "WallTypeStoneWall",
  "WallTypeStoneWallLine", "WarboatCount", "WoodAmount", "$accept",
  "aiscript", "rules", "rule", "conditions", "condition", "conditiontype",
  "actions", "singleaction", "age", "building", "civ", "commodity",
  "difficultylevel", "difficultyparameter", "diplomaticstance",
  "mapsizetype", "maptypename", "playernumbertype", "relop",
  "researchitem", "startingresourcestype", "strategicnumbername", "unit",
  "victoryconditionname", "walltype", "acknowledgeevent",
  "acknowledgetaunt", "attacknow", "build", "buildforward", "buildgate",
  "buildwall", "buycommodity", "ccaddresource", "chatlocal",
  "chatlocaltoself", "chatlocalusingid", "chatlocalusingrange",
  "chattoall", "chattoallusingid", "chattoallusingrange", "chattoallies",
  "chattoalliesusingid", "chattoalliesusingrange", "chattoenemies",
  "chattoenemiesusingid", "chattoenemiesusingrange", "chattoplayer",
  "chattoplayerusingid", "chattoplayerusingrange", "chattrace",
  "cleartributememory", "deletebuilding", "deleteunit", "disableself",
  "disabletimer", "donothing", "enabletimer", "enablewallplacement",
  "generaterandomnumber", "log", "logtrace", "releaseescrow", "research",
  "resign", "sellcommodity", "setdifficultyparameter", "setdoctrine",
  "setescrowpercentage", "setgoal", "setsharedgoal", "setsignal",
  "setstance", "setstrategicnumber", "spy", "taunt", "tauntusingrange",
  "train", "tributetoplayer", "action", "trueval", "falseval",
  "attacksoldiercount", "attackwarboatcount", "buildingavailable",
  "buildingcount", "buildingcounttotal", "buildingtypecount",
  "buildingtypecounttotal", "canaffordbuilding", "canaffordcompletewall",
  "canaffordresearch", "canaffordunit", "canbuild", "canbuildgate",
  "canbuildgatewithescrow", "canbuildwall", "canbuildwallwithescrow",
  "canbuildwithescrow", "canbuycommodity", "canresearch",
  "canresearchwithescrow", "cansellcommodity", "canspy",
  "canspywithescrow", "cantrain", "cantrainwithescrow",
  "ccplayersbuildingcount", "ccplayersbuildingtypecount",
  "ccplayersunitcount", "ccplayersunittypecount", "cheatsenabled",
  "civselected", "civilianpopulation", "commoditybuyingprice",
  "commoditysellingprice", "currentage", "currentagetime", "currentscore",
  "deathmatchgame", "defendsoldiercount", "defendwarboatcount",
  "difficulty", "doctrine", "dropsitemindistance", "enemybuildingsintown",
  "enemycapturedrelics", "escrowamount", "eventdetected", "foodamount",
  "gametime", "goal", "goldamount", "housingheadroom", "idlefarmcount",
  "mapsize", "maptype", "militarypopulation", "playercomputer",
  "playerhuman", "playeringame", "playernumber", "playerresigned",
  "playervalid", "playersbuildingcount", "playersbuildingtypecount",
  "playersciv", "playerscivilianpopulation", "playerscurrentage",
  "playerscurrentagetime", "playersmilitarypopulation",
  "playerspopulation", "playersscore", "playersstance", "playerstribute",
  "playerstributememory", "playersunitcount", "playersunittypecount",
  "population", "populationcap", "populationheadroom", "randomnumber",
  "regicidegame", "researchavailable", "researchcompleted",
  "resourcefound", "sharedgoal", "sheepandforagetoofar", "soldiercount",
  "stancetoward", "startingage", "startingresources", "stoneamount",
  "strategicnumber", "tauntdetected", "timertriggered", "townunderattack",
  "unitavailable", "unitcount", "unitcounttotal", "unittypecount",
  "unittypecounttotal", "victorycondition", "wallcompletedpercentage",
  "wallinvisiblepercentage", "warboatcount", "woodamount", "fact", YY_NULLPTR
  };

#if YYDEBUG
  const short
  ScriptParser::yyrline_[] =
  {
       0,   603,   603,   605,   609,   610,   613,   616,   617,   620,
     623,   624,   625,   629,   630,   633,   636,   637,   638,   639,
     640,   641,   644,   645,   646,   647,   648,   649,   650,   651,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,   667,   670,   671,   672,   673,
     674,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     686,   687,   688,   689,   692,   693,   694,   695,   696,   699,
     700,   703,   704,   705,   708,   709,   710,   711,   712,   713,
     716,   717,   718,   719,   720,   721,   722,   723,   724,   725,
     726,   727,   728,   729,   730,   731,   734,   735,   736,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   753,   754,   755,   756,   757,   758,   761,
     762,   763,   764,   765,   766,   767,   768,   769,   770,   771,
     772,   773,   774,   775,   776,   777,   778,   779,   780,   781,
     782,   783,   784,   785,   786,   787,   788,   789,   790,   791,
     792,   793,   794,   795,   796,   797,   798,   799,   800,   801,
     802,   803,   804,   805,   806,   807,   808,   809,   810,   811,
     812,   813,   814,   815,   816,   817,   818,   819,   820,   821,
     822,   823,   824,   825,   826,   827,   828,   829,   830,   831,
     832,   833,   834,   835,   836,   837,   838,   839,   840,   841,
     842,   843,   844,   845,   846,   847,   848,   849,   850,   851,
     852,   853,   854,   855,   856,   857,   858,   859,   860,   861,
     862,   863,   864,   865,   866,   867,   868,   869,   870,   871,
     872,   873,   874,   875,   876,   877,   880,   881,   882,   885,
     886,   887,   888,   889,   890,   891,   892,   893,   894,   895,
     896,   897,   898,   899,   900,   901,   902,   903,   904,   905,
     906,   907,   908,   909,   910,   911,   912,   913,   914,   915,
     916,   917,   918,   919,   920,   921,   922,   923,   924,   925,
     926,   927,   928,   929,   930,   931,   932,   933,   934,   935,
     936,   937,   938,   939,   940,   941,   942,   943,   944,   945,
     946,   947,   948,   949,   950,   951,   952,   953,   954,   955,
     956,   957,   958,   959,   960,   961,   962,   963,   964,   965,
     966,   967,   968,   969,   970,   971,   972,   973,   974,   975,
     976,   977,   978,   979,   980,   981,   982,   983,   984,   985,
     986,   987,   988,   989,   990,   991,   992,   993,   994,   995,
     996,   997,   998,   999,  1000,  1001,  1002,  1003,  1004,  1005,
    1006,  1007,  1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,
    1016,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,
    1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,
    1038,  1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,
    1048,  1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,
    1058,  1059,  1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,
    1068,  1069,  1070,  1071,  1072,  1073,  1074,  1075,  1076,  1077,
    1078,  1079,  1080,  1081,  1082,  1083,  1084,  1085,  1086,  1087,
    1088,  1089,  1090,  1091,  1092,  1093,  1094,  1095,  1096,  1097,
    1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,
    1108,  1109,  1110,  1111,  1112,  1113,  1114,  1115,  1116,  1117,
    1118,  1119,  1120,  1121,  1122,  1123,  1124,  1125,  1126,  1127,
    1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,
    1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,
    1148,  1149,  1150,  1153,  1154,  1155,  1156,  1157,  1160,  1161,
    1162,  1163,  1167,  1170,  1173,  1176,  1179,  1182,  1185,  1188,
    1191,  1194,  1197,  1200,  1203,  1206,  1209,  1212,  1215,  1218,
    1221,  1224,  1227,  1230,  1233,  1236,  1239,  1242,  1245,  1248,
    1251,  1254,  1257,  1260,  1263,  1266,  1269,  1272,  1275,  1278,
    1281,  1283,  1286,  1289,  1292,  1295,  1298,  1301,  1304,  1307,
    1310,  1313,  1316,  1319,  1322,  1325,  1328,  1332,  1333,  1334,
    1335,  1336,  1337,  1338,  1339,  1340,  1341,  1342,  1343,  1344,
    1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1353,  1354,
    1355,  1356,  1357,  1358,  1359,  1360,  1361,  1362,  1363,  1364,
    1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,  1373,  1374,
    1375,  1376,  1377,  1378,  1379,  1380,  1381,  1382,  1383,  1384,
    1385,  1389,  1392,  1395,  1398,  1401,  1404,  1407,  1410,  1413,
    1416,  1419,  1422,  1425,  1428,  1431,  1434,  1437,  1440,  1443,
    1446,  1449,  1450,  1453,  1454,  1457,  1460,  1463,  1466,  1469,
    1472,  1475,  1478,  1481,  1484,  1487,  1490,  1493,  1496,  1499,
    1502,  1505,  1508,  1511,  1514,  1517,  1520,  1523,  1526,  1529,
    1532,  1535,  1538,  1541,  1544,  1547,  1550,  1553,  1556,  1559,
    1562,  1565,  1568,  1571,  1574,  1577,  1580,  1583,  1586,  1589,
    1592,  1595,  1598,  1601,  1604,  1607,  1610,  1613,  1616,  1619,
    1622,  1625,  1628,  1631,  1634,  1637,  1640,  1643,  1646,  1649,
    1652,  1655,  1658,  1661,  1664,  1667,  1670,  1673,  1676,  1679,
    1682,  1685,  1688,  1691,  1694,  1697,  1700,  1703,  1706,  1709,
    1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,  1720,  1721,
    1722,  1723,  1724,  1725,  1726,  1727,  1728,  1729,  1730,  1731,
    1732,  1733,  1734,  1735,  1736,  1737,  1738,  1739,  1740,  1741,
    1742,  1743,  1744,  1745,  1746,  1747,  1748,  1749,  1750,  1751,
    1752,  1753,  1754,  1755,  1756,  1757,  1758,  1759,  1760,  1761,
    1762,  1763,  1764,  1765,  1766,  1767,  1768,  1769,  1770,  1771,
    1772,  1773,  1774,  1775,  1776,  1777,  1778,  1779,  1780,  1781,
    1782,  1783,  1784,  1785,  1786,  1787,  1788,  1789,  1790,  1791,
    1792,  1793,  1794,  1795,  1796,  1797,  1798,  1799,  1800,  1801,
    1802,  1803,  1804,  1805,  1806,  1807,  1808,  1809,  1810,  1811,
    1812,  1813,  1814,  1815,  1816,  1817,  1818
  };

  // Print the state stack on the debug stream.
  void
  ScriptParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  ScriptParser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 9 "grammar.gen.ypp"
} //  ai 
#line 9402 "grammar.gen.tab.cpp"

#line 1820 "grammar.gen.ypp"


#ifdef PARSER_TEST
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Please pass a file as argument" << std::endl;
        return 1;
    }
    std::ifstream in(argv[1]);
    ai::ScriptLoader parser(0);
    return parser.parse(in, std::cout);
}
#endif

void ai::ScriptParser::error(const location_type &loc, const std::string& message) {
    std::cerr << "parser error: " << message << " at line " << loc.begin.line << " to " << loc.end.line << std::endl;
}
