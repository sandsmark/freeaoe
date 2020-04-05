// A Bison parser, made by GNU Bison 3.5.3.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file grammar.gen.tab.hpp
 ** Define the  ai ::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_YY_GRAMMAR_GEN_TAB_HPP_INCLUDED
# define YY_YY_GRAMMAR_GEN_TAB_HPP_INCLUDED
// "%code requires" blocks.
#line 21 "grammar.gen.ypp"

    #include "gen/enums.h"
    #include "AiRule.h"
    #include "AiScript.h"
    #include <memory>

    namespace ai {
        class ScriptTokenizer;
        class ScriptLoader;
    }

    #ifndef YYDEBUG
        #define YYDEBUG 1
    #endif

    #define YY_NULLPTR nullptr

#line 66 "grammar.gen.tab.hpp"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 9 "grammar.gen.ypp"
namespace  ai  {
#line 201 "grammar.gen.tab.hpp"




  /// A Bison parser.
  class ScriptParser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator= (const self_type&);
    semantic_type (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // AcknowledgeEvent
      // AcknowledgeTaunt
      // AttackNow
      // Build
      // BuildForward
      // BuildGate
      // BuildWall
      // BuyCommodity
      // CcAddResource
      // ChatLocal
      // ChatLocalToSelf
      // ChatLocalUsingId
      // ChatLocalUsingRange
      // ChatToAll
      // ChatToAllies
      // ChatToAlliesUsingId
      // ChatToAlliesUsingRange
      // ChatToAllUsingId
      // ChatToAllUsingRange
      // ChatToEnemies
      // ChatToEnemiesUsingId
      // ChatToEnemiesUsingRange
      // ChatToPlayer
      // ChatToPlayerUsingId
      // ChatToPlayerUsingRange
      // ChatTrace
      // ClearTributeMemory
      // DeleteBuilding
      // DeleteUnit
      // DisableSelf
      // DisableTimer
      // DoNothing
      // EnableTimer
      // EnableWallPlacement
      // GenerateRandomNumber
      // Log
      // LogTrace
      // ReleaseEscrow
      // Research
      // Resign
      // SellCommodity
      // SetDifficultyParameter
      // SetDoctrine
      // SetEscrowPercentage
      // SetGoal
      // SetSharedGoal
      // SetSignal
      // SetStance
      // SetStrategicNumber
      // Spy
      // Taunt
      // TauntUsingRange
      // Train
      // TributeToPlayer
      char dummy1[sizeof (ActionType)];

      // age
      char dummy2[sizeof (Age)];

      // building
      char dummy3[sizeof (Building)];

      // civ
      char dummy4[sizeof (Civ)];

      // commodity
      char dummy5[sizeof (Commodity)];

      // difficultylevel
      char dummy6[sizeof (DifficultyLevel)];

      // difficultyparameter
      char dummy7[sizeof (DifficultyParameter)];

      // diplomaticstance
      char dummy8[sizeof (DiplomaticStance)];

      // AttackSoldierCount
      // AttackWarboatCount
      // BuildingAvailable
      // BuildingCount
      // BuildingCountTotal
      // BuildingTypeCount
      // BuildingTypeCountTotal
      // CanAffordBuilding
      // CanAffordCompleteWall
      // CanAffordResearch
      // CanAffordUnit
      // CanBuild
      // CanBuildGate
      // CanBuildGateWithEscrow
      // CanBuildWall
      // CanBuildWallWithEscrow
      // CanBuildWithEscrow
      // CanBuyCommodity
      // CanResearch
      // CanResearchWithEscrow
      // CanSellCommodity
      // CanSpy
      // CanSpyWithEscrow
      // CanTrain
      // CanTrainWithEscrow
      // CcPlayersBuildingCount
      // CcPlayersBuildingTypeCount
      // CcPlayersUnitCount
      // CcPlayersUnitTypeCount
      // CheatsEnabled
      // CivilianPopulation
      // CivSelected
      // CommodityBuyingPrice
      // CommoditySellingPrice
      // CurrentAge
      // CurrentAgeTime
      // CurrentScore
      // DeathMatchGame
      // DefendSoldierCount
      // DefendWarboatCount
      // Difficulty
      // Doctrine
      // DropsiteMinDistance
      // EnemyBuildingsInTown
      // EnemyCapturedRelics
      // EscrowAmount
      // EventDetected
      // Falseval
      // FoodAmount
      // GameTime
      // Goal
      // GoldAmount
      // HousingHeadroom
      // IdleFarmCount
      // MapSize
      // MapType
      // MilitaryPopulation
      // PlayerComputer
      // PlayerHuman
      // PlayerInGame
      // PlayerNumber
      // PlayerResigned
      // PlayersBuildingCount
      // PlayersBuildingTypeCount
      // PlayersCiv
      // PlayersCivilianPopulation
      // PlayersCurrentAge
      // PlayersCurrentAgeTime
      // PlayersMilitaryPopulation
      // PlayersPopulation
      // PlayersScore
      // PlayersStance
      // PlayersTribute
      // PlayersTributeMemory
      // PlayersUnitCount
      // PlayersUnitTypeCount
      // PlayerValid
      // Population
      // PopulationCap
      // PopulationHeadroom
      // RandomNumber
      // RegicideGame
      // ResearchAvailable
      // ResearchCompleted
      // ResourceFound
      // SharedGoal
      // SheepAndForageTooFar
      // SoldierCount
      // StanceToward
      // StartingAge
      // StartingResources
      // StoneAmount
      // StrategicNumber
      // TauntDetected
      // TimerTriggered
      // TownUnderAttack
      // Trueval
      // UnitAvailable
      // UnitCount
      // UnitCountTotal
      // UnitTypeCount
      // UnitTypeCountTotal
      // VictoryCondition
      // WallCompletedPercentage
      // WallInvisiblePercentage
      // WarboatCount
      // WoodAmount
      char dummy9[sizeof (Fact)];

      // mapsizetype
      char dummy10[sizeof (MapSizeType)];

      // maptypename
      char dummy11[sizeof (MapTypeName)];

      // playernumbertype
      char dummy12[sizeof (PlayerNumberType)];

      // relop
      char dummy13[sizeof (RelOp)];

      // researchitem
      char dummy14[sizeof (ResearchItem)];

      // startingresourcestype
      char dummy15[sizeof (StartingResourcesType)];

      // strategicnumbername
      char dummy16[sizeof (StrategicNumberName)];

      // unit
      char dummy17[sizeof (Unit)];

      // victoryconditionname
      char dummy18[sizeof (VictoryConditionName)];

      // walltype
      char dummy19[sizeof (WallType)];

      // Number
      char dummy20[sizeof (int)];

      // singleaction
      // acknowledgeevent
      // acknowledgetaunt
      // attacknow
      // build
      // buildforward
      // buildgate
      // buildwall
      // buycommodity
      // ccaddresource
      // chatlocal
      // chatlocaltoself
      // chatlocalusingid
      // chatlocalusingrange
      // chattoall
      // chattoallusingid
      // chattoallusingrange
      // chattoallies
      // chattoalliesusingid
      // chattoalliesusingrange
      // chattoenemies
      // chattoenemiesusingid
      // chattoenemiesusingrange
      // chattoplayer
      // chattoplayerusingid
      // chattoplayerusingrange
      // chattrace
      // cleartributememory
      // deletebuilding
      // deleteunit
      // disableself
      // disabletimer
      // donothing
      // enabletimer
      // enablewallplacement
      // generaterandomnumber
      // log
      // logtrace
      // releaseescrow
      // research
      // resign
      // sellcommodity
      // setdifficultyparameter
      // setdoctrine
      // setescrowpercentage
      // setgoal
      // setsharedgoal
      // setsignal
      // setstance
      // setstrategicnumber
      // spy
      // taunt
      // tauntusingrange
      // train
      // tributetoplayer
      // action
      char dummy21[sizeof (std::shared_ptr<ai::Action>)];

      // rule
      char dummy22[sizeof (std::shared_ptr<ai::AiRule>)];

      // condition
      // conditiontype
      // trueval
      // falseval
      // attacksoldiercount
      // attackwarboatcount
      // buildingavailable
      // buildingcount
      // buildingcounttotal
      // buildingtypecount
      // buildingtypecounttotal
      // canaffordbuilding
      // canaffordcompletewall
      // canaffordresearch
      // canaffordunit
      // canbuild
      // canbuildgate
      // canbuildgatewithescrow
      // canbuildwall
      // canbuildwallwithescrow
      // canbuildwithescrow
      // canbuycommodity
      // canresearch
      // canresearchwithescrow
      // cansellcommodity
      // canspy
      // canspywithescrow
      // cantrain
      // cantrainwithescrow
      // ccplayersbuildingcount
      // ccplayersbuildingtypecount
      // ccplayersunitcount
      // ccplayersunittypecount
      // cheatsenabled
      // civselected
      // civilianpopulation
      // commoditybuyingprice
      // commoditysellingprice
      // currentage
      // currentagetime
      // currentscore
      // deathmatchgame
      // defendsoldiercount
      // defendwarboatcount
      // difficulty
      // doctrine
      // dropsitemindistance
      // enemybuildingsintown
      // enemycapturedrelics
      // escrowamount
      // eventdetected
      // foodamount
      // gametime
      // goal
      // goldamount
      // housingheadroom
      // idlefarmcount
      // mapsize
      // maptype
      // militarypopulation
      // playercomputer
      // playerhuman
      // playeringame
      // playernumber
      // playerresigned
      // playervalid
      // playersbuildingcount
      // playersbuildingtypecount
      // playersciv
      // playerscivilianpopulation
      // playerscurrentage
      // playerscurrentagetime
      // playersmilitarypopulation
      // playerspopulation
      // playersscore
      // playersstance
      // playerstribute
      // playerstributememory
      // playersunitcount
      // playersunittypecount
      // population
      // populationcap
      // populationheadroom
      // randomnumber
      // regicidegame
      // researchavailable
      // researchcompleted
      // resourcefound
      // sharedgoal
      // sheepandforagetoofar
      // soldiercount
      // stancetoward
      // startingage
      // startingresources
      // stoneamount
      // strategicnumber
      // tauntdetected
      // timertriggered
      // townunderattack
      // unitavailable
      // unitcount
      // unitcounttotal
      // unittypecount
      // unittypecounttotal
      // victorycondition
      // wallcompletedpercentage
      // wallinvisiblepercentage
      // warboatcount
      // woodamount
      // fact
      char dummy23[sizeof (std::shared_ptr<ai::Condition>)];

      // String
      // SymbolName
      char dummy24[sizeof (std::string)];

      // actions
      char dummy25[sizeof (std::vector<std::shared_ptr<ai::Action>>)];

      // conditions
      char dummy26[sizeof (std::vector<std::shared_ptr<ai::Condition>>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        ScriptEnd = 0,
        Number = 258,
        String = 259,
        SymbolName = 260,
        OpenParen = 261,
        CloseParen = 262,
        RuleStart = 263,
        ConditionActionSeparator = 264,
        Not = 265,
        Or = 266,
        LoadIfDefined = 267,
        Else = 268,
        EndIf = 269,
        Space = 270,
        NewLine = 271,
        AcknowledgeEvent = 272,
        AcknowledgeTaunt = 273,
        AgeDarkAge = 274,
        AgeFeudalAge = 275,
        AgeCastleAge = 276,
        AgeImperialAge = 277,
        AgePostImperialAge = 278,
        AttackNow = 279,
        AttackSoldierCount = 280,
        AttackWarboatCount = 281,
        Build = 282,
        BuildForward = 283,
        BuildGate = 284,
        BuildingArcheryRange = 285,
        BuildingBarracks = 286,
        BuildingBlacksmith = 287,
        BuildingBombardTower = 288,
        BuildingCastle = 289,
        BuildingDock = 290,
        BuildingFarm = 291,
        BuildingFishTrap = 292,
        BuildingGuardTower = 293,
        BuildingHouse = 294,
        BuildingKeep = 295,
        BuildingLumberCamp = 296,
        BuildingMarket = 297,
        BuildingMill = 298,
        BuildingMiningCamp = 299,
        BuildingMonastery = 300,
        BuildingOutpost = 301,
        BuildingSiegeWorkshop = 302,
        BuildingStable = 303,
        BuildingTownCenter = 304,
        BuildingUniversity = 305,
        BuildingWatchTower = 306,
        BuildingWonder = 307,
        BuildingWatchTowerLine = 308,
        BuildingAvailable = 309,
        BuildingCount = 310,
        BuildingCountTotal = 311,
        BuildingTypeCount = 312,
        BuildingTypeCountTotal = 313,
        BuildWall = 314,
        BuyCommodity = 315,
        CanAffordBuilding = 316,
        CanAffordCompleteWall = 317,
        CanAffordResearch = 318,
        CanAffordUnit = 319,
        CanBuild = 320,
        CanBuildGate = 321,
        CanBuildGateWithEscrow = 322,
        CanBuildWall = 323,
        CanBuildWallWithEscrow = 324,
        CanBuildWithEscrow = 325,
        CanBuyCommodity = 326,
        CanResearch = 327,
        CanResearchWithEscrow = 328,
        CanSellCommodity = 329,
        CanSpy = 330,
        CanSpyWithEscrow = 331,
        CanTrain = 332,
        CanTrainWithEscrow = 333,
        CcAddResource = 334,
        CcPlayersBuildingCount = 335,
        CcPlayersBuildingTypeCount = 336,
        CcPlayersUnitCount = 337,
        CcPlayersUnitTypeCount = 338,
        ChatLocal = 339,
        ChatLocalToSelf = 340,
        ChatLocalUsingId = 341,
        ChatLocalUsingRange = 342,
        ChatToAll = 343,
        ChatToAllies = 344,
        ChatToAlliesUsingId = 345,
        ChatToAlliesUsingRange = 346,
        ChatToAllUsingId = 347,
        ChatToAllUsingRange = 348,
        ChatToEnemies = 349,
        ChatToEnemiesUsingId = 350,
        ChatToEnemiesUsingRange = 351,
        ChatToPlayer = 352,
        ChatToPlayerUsingId = 353,
        ChatToPlayerUsingRange = 354,
        ChatTrace = 355,
        CheatsEnabled = 356,
        CivBriton = 357,
        CivByzantine = 358,
        CivCeltic = 359,
        CivChinese = 360,
        CivFrankish = 361,
        CivGothic = 362,
        CivJapanese = 363,
        CivMongol = 364,
        CivPersian = 365,
        CivSaracen = 366,
        CivTeutonic = 367,
        CivTurkish = 368,
        CivViking = 369,
        CivMyCiv = 370,
        CivilianPopulation = 371,
        CivSelected = 372,
        ClearTributeMemory = 373,
        CommodityBuyingPrice = 374,
        CommodityFood = 375,
        CommodityStone = 376,
        CommodityWood = 377,
        CommodityGold = 378,
        CommoditySellingPrice = 379,
        CurrentAge = 380,
        CurrentAgeTime = 381,
        CurrentScore = 382,
        DeathMatchGame = 383,
        DefendSoldierCount = 384,
        DefendWarboatCount = 385,
        DeleteBuilding = 386,
        DeleteUnit = 387,
        Difficulty = 388,
        DifficultyLevelEasiest = 389,
        DifficultyLevelEasy = 390,
        DifficultyLevelModerate = 391,
        DifficultyLevelHard = 392,
        DifficultyLevelHardest = 393,
        DifficultyParameterAbilityToDodgeMissiles = 394,
        DifficultyParameterAbilityToMaintainDistance = 395,
        DiplomaticStanceAlly = 396,
        DiplomaticStanceNeutral = 397,
        DiplomaticStanceEnemy = 398,
        DisableSelf = 399,
        DisableTimer = 400,
        Doctrine = 401,
        DoNothing = 402,
        DropsiteMinDistance = 403,
        EnableTimer = 404,
        EnableWallPlacement = 405,
        EnemyBuildingsInTown = 406,
        EnemyCapturedRelics = 407,
        EscrowAmount = 408,
        EventDetected = 409,
        Falseval = 410,
        FoodAmount = 411,
        GameTime = 412,
        GenerateRandomNumber = 413,
        Goal = 414,
        GoldAmount = 415,
        HousingHeadroom = 416,
        IdleFarmCount = 417,
        Log = 418,
        LogTrace = 419,
        MapSize = 420,
        MapSizeTypeTiny = 421,
        MapSizeTypeSmall = 422,
        MapSizeTypeMedium = 423,
        MapSizeTypeNormal = 424,
        MapSizeTypeLarge = 425,
        MapSizeTypeGiant = 426,
        MapType = 427,
        MapTypeNameArabia = 428,
        MapTypeNameArchipelago = 429,
        MapTypeNameBaltic = 430,
        MapTypeNameBlackForest = 431,
        MapTypeNameCoastal = 432,
        MapTypeNameContinental = 433,
        MapTypeNameCraterLake = 434,
        MapTypeNameFortress = 435,
        MapTypeNameGoldRush = 436,
        MapTypeNameHighland = 437,
        MapTypeNameIslands = 438,
        MapTypeNameMediterranean = 439,
        MapTypeNameMigration = 440,
        MapTypeNameRivers = 441,
        MapTypeNameTeamIslands = 442,
        MapTypeNameScenarioMap = 443,
        MilitaryPopulation = 444,
        PlayerComputer = 445,
        PlayerHuman = 446,
        PlayerInGame = 447,
        PlayerNumber = 448,
        PlayerNumberTypeAnyAlly = 449,
        PlayerNumberTypeAnyComputer = 450,
        PlayerNumberTypeAnyComputerAlly = 451,
        PlayerNumberTypeAnyComputerEnemy = 452,
        PlayerNumberTypeAnyComputerNeutral = 453,
        PlayerNumberTypeAnyEnemy = 454,
        PlayerNumberTypeAnyHuman = 455,
        PlayerNumberTypeAnyHumanAlly = 456,
        PlayerNumberTypeAnyHumanEnemy = 457,
        PlayerNumberTypeAnyHumanNeutral = 458,
        PlayerNumberTypeAnyNeutral = 459,
        PlayerNumberTypeEveryAlly = 460,
        PlayerNumberTypeEveryComputer = 461,
        PlayerNumberTypeEveryEnemy = 462,
        PlayerNumberTypeEveryHuman = 463,
        PlayerNumberTypeEveryNeutral = 464,
        PlayerNumberTypeMyPlayerNumber = 465,
        PlayerResigned = 466,
        PlayersBuildingCount = 467,
        PlayersBuildingTypeCount = 468,
        PlayersCiv = 469,
        PlayersCivilianPopulation = 470,
        PlayersCurrentAge = 471,
        PlayersCurrentAgeTime = 472,
        PlayersMilitaryPopulation = 473,
        PlayersPopulation = 474,
        PlayersScore = 475,
        PlayersStance = 476,
        PlayersTribute = 477,
        PlayersTributeMemory = 478,
        PlayersUnitCount = 479,
        PlayersUnitTypeCount = 480,
        PlayerValid = 481,
        Population = 482,
        PopulationCap = 483,
        PopulationHeadroom = 484,
        RandomNumber = 485,
        RegicideGame = 486,
        ReleaseEscrow = 487,
        RelOpLessThan = 488,
        RelOpLessOrEqual = 489,
        RelOpGreaterThan = 490,
        RelOpGreaterOrEqual = 491,
        RelOpEqual = 492,
        RelOpNotEqual = 493,
        Research = 494,
        ResearchAvailable = 495,
        ResearchCompleted = 496,
        ResearchItemRiArbalest = 497,
        ResearchItemRiCrossbow = 498,
        ResearchItemRiEliteSkirmisher = 499,
        ResearchItemRiHandCannon = 500,
        ResearchItemRiHeavyCavalryArcher = 501,
        ResearchItemRiChampion = 502,
        ResearchItemRiEliteEagleWarrior = 503,
        ResearchItemRiHalberdier = 504,
        ResearchItemRiLongSwordsman = 505,
        ResearchItemRiManAtArms = 506,
        ResearchItemRiParthianTactics = 507,
        ResearchItemRiPikeman = 508,
        ResearchItemRiSquires = 509,
        ResearchItemRiThumbRing = 510,
        ResearchItemRiTracking = 511,
        ResearchItemRiTwoHandedSwordsman = 512,
        ResearchItemRiBlastFurnace = 513,
        ResearchItemRiBodkinArrow = 514,
        ResearchItemRiBracer = 515,
        ResearchItemRiChainBarding = 516,
        ResearchItemRiChainMail = 517,
        ResearchItemRiFletching = 518,
        ResearchItemRiForging = 519,
        ResearchItemRiIronCasting = 520,
        ResearchItemRiLeatherArcherArmor = 521,
        ResearchItemRiPaddedArcherArmor = 522,
        ResearchItemRiPlateBarding = 523,
        ResearchItemRiPlateMail = 524,
        ResearchItemRiRingArcherArmor = 525,
        ResearchItemRiScaleBarding = 526,
        ResearchItemRiScaleMail = 527,
        ResearchItemRiConscription = 528,
        ResearchItemRiHoardings = 529,
        ResearchItemRiSappers = 530,
        ResearchItemRiEliteBerserk = 531,
        ResearchItemRiEliteCataphract = 532,
        ResearchItemRiEliteChuKoNu = 533,
        ResearchItemRiEliteHuskarl = 534,
        ResearchItemRiEliteJanissary = 535,
        ResearchItemRiEliteLongbowman = 536,
        ResearchItemRiEliteMameluke = 537,
        ResearchItemRiEliteMangudai = 538,
        ResearchItemRiEliteSamurai = 539,
        ResearchItemRiEliteTeutonicKnight = 540,
        ResearchItemRiEliteThrowingAxeman = 541,
        ResearchItemRiEliteWarElephant = 542,
        ResearchItemRiEliteWoadRaider = 543,
        ResearchItemRiMyUniqueEliteUnit = 544,
        ResearchItemRiMyUniqueResearch = 545,
        ResearchItemRiCannonGalleon = 546,
        ResearchItemRiCareening = 547,
        ResearchItemRiDeckGuns = 548,
        ResearchItemRiDryDock = 549,
        ResearchItemRiEliteLongboat = 550,
        ResearchItemRiFastFireShip = 551,
        ResearchItemRiGalleon = 552,
        ResearchItemRiHeavyDemolitionShip = 553,
        ResearchItemRiShipwright = 554,
        ResearchItemRiWarGalley = 555,
        ResearchItemRiBowSaw = 556,
        ResearchItemRiDoubleBitAxe = 557,
        ResearchItemRiTwoManSaw = 558,
        ResearchItemRiBanking = 559,
        ResearchItemRiCaravan = 560,
        ResearchItemRiCartography = 561,
        ResearchItemRiCoinage = 562,
        ResearchItemRiGuilds = 563,
        ResearchItemRiCropRotation = 564,
        ResearchItemRiHeavyPlow = 565,
        ResearchItemRiHorseCollar = 566,
        ResearchItemRiGoldMining = 567,
        ResearchItemRiGoldShaftMining = 568,
        ResearchItemRiStoneMining = 569,
        ResearchItemRiStoneShaftMining = 570,
        ResearchItemRiAtonement = 571,
        ResearchItemRiBlockPrinting = 572,
        ResearchItemRiFaith = 573,
        ResearchItemRiFervor = 574,
        ResearchItemRiHerbalMedicine = 575,
        ResearchItemRiHeresy = 576,
        ResearchItemRiIllumination = 577,
        ResearchItemRiRedemption = 578,
        ResearchItemRiSanctity = 579,
        ResearchItemRiTheocracy = 580,
        ResearchItemRiBombardCannon = 581,
        ResearchItemRiCappedRam = 582,
        ResearchItemRiHeavyScorpion = 583,
        ResearchItemRiOnager = 584,
        ResearchItemRiScorpion = 585,
        ResearchItemRiSiegeOnager = 586,
        ResearchItemRiSiegeRam = 587,
        ResearchItemRiBloodlines = 588,
        ResearchItemRiCavalier = 589,
        ResearchItemRiHeavyCamel = 590,
        ResearchItemRiHusbandry = 591,
        ResearchItemRiHussar = 592,
        ResearchItemRiLightCavalry = 593,
        ResearchItemRiPaladin = 594,
        ResearchItemRiHandCart = 595,
        ResearchItemRiLoom = 596,
        ResearchItemRiTownPatrol = 597,
        ResearchItemRiTownWatch = 598,
        ResearchItemRiWheelBarrow = 599,
        ResearchItemRiArchitecture = 600,
        ResearchItemRiBallistics = 601,
        ResearchItemRiBombardTower = 602,
        ResearchItemRiChemistry = 603,
        ResearchItemRiFortifiedWall = 604,
        ResearchItemRiGuardTower = 605,
        ResearchItemRiHeatedShot = 606,
        ResearchItemRiKeep = 607,
        ResearchItemRiMasonry = 608,
        ResearchItemRiMurderHoles = 609,
        ResearchItemRiSiegeEngineers = 610,
        ResearchItemRiStonecutting = 611,
        ResearchItemMyUniqueUnitUpgrade = 612,
        ResearchItemMyUniqueResearch = 613,
        Resign = 614,
        ResourceFound = 615,
        SellCommodity = 616,
        SetDifficultyParameter = 617,
        SetDoctrine = 618,
        SetEscrowPercentage = 619,
        SetGoal = 620,
        SetSharedGoal = 621,
        SetSignal = 622,
        SetStance = 623,
        SetStrategicNumber = 624,
        SharedGoal = 625,
        SheepAndForageTooFar = 626,
        SoldierCount = 627,
        Spy = 628,
        StanceToward = 629,
        StartingAge = 630,
        StartingResources = 631,
        StartingResourcesTypeLowResources = 632,
        StartingResourcesTypeMediumResources = 633,
        StartingResourcesTypeHighResources = 634,
        StoneAmount = 635,
        StrategicNumber = 636,
        StrategicNumberNameSnPercentCivilianExplorers = 637,
        StrategicNumberNameSnPercentCivilianBuilders = 638,
        StrategicNumberNameSnPercentCivilianGatherers = 639,
        StrategicNumberNameSnCapCivilianExplorers = 640,
        StrategicNumberNameSnCapCivilianBuilders = 641,
        StrategicNumberNameSnCapCivilianGatherers = 642,
        StrategicNumberNameSnMinimumAttackGroupSize = 643,
        StrategicNumberNameSnTotalNumberExplorers = 644,
        StrategicNumberNameSnPercentEnemySightedResponse = 645,
        StrategicNumberNameSnEnemySightedResponseDistance = 646,
        StrategicNumberNameSnSentryDistance = 647,
        StrategicNumberNameSnRelicReturnDistance = 648,
        StrategicNumberNameSnMinimumDefendGroupSize = 649,
        StrategicNumberNameSnMaximumAttackGroupSize = 650,
        StrategicNumberNameSnMaximumDefendGroupSize = 651,
        StrategicNumberNameSnMinimumPeaceLikeLevel = 652,
        StrategicNumberNameSnPercentExplorationRequired = 653,
        StrategicNumberNameSnZeroPriorityDistance = 654,
        StrategicNumberNameSnMinimumCivilianExplorers = 655,
        StrategicNumberNameSnNumberAttackGroups = 656,
        StrategicNumberNameSnNumberDefendGroups = 657,
        StrategicNumberNameSnAttackGroupGatherSpacing = 658,
        StrategicNumberNameSnNumberExploreGroups = 659,
        StrategicNumberNameSnMinimumExploreGroupSize = 660,
        StrategicNumberNameSnMaximumExploreGroupSize = 661,
        StrategicNumberNameSnGoldDefendPriority = 662,
        StrategicNumberNameSnStoneDefendPriority = 663,
        StrategicNumberNameSnForageDefendPriority = 664,
        StrategicNumberNameSnRelicDefendPriority = 665,
        StrategicNumberNameSnTownDefendPriority = 666,
        StrategicNumberNameSnDefenseDistance = 667,
        StrategicNumberNameSnNumberBoatAttackGroups = 668,
        StrategicNumberNameSnMinimumBoatAttackGroupSize = 669,
        StrategicNumberNameSnMaximumBoatAttackGroupSize = 670,
        StrategicNumberNameSnNumberBoatExploreGroups = 671,
        StrategicNumberNameSnMinimumBoatExploreGroupSize = 672,
        StrategicNumberNameSnMaximumBoatExploreGroupSize = 673,
        StrategicNumberNameSnNumberBoatDefendGroups = 674,
        StrategicNumberNameSnMinimumBoatDefendGroupSize = 675,
        StrategicNumberNameSnMaximumBoatDefendGroupSize = 676,
        StrategicNumberNameSnDockDefendPriority = 677,
        StrategicNumberNameSnSentryDistanceVariation = 678,
        StrategicNumberNameSnMinimumTownSize = 679,
        StrategicNumberNameSnMaximumTownSize = 680,
        StrategicNumberNameSnGroupCommanderSelectionMethod = 681,
        StrategicNumberNameSnConsecutiveIdleUnitLimit = 682,
        StrategicNumberNameSnTargetEvaluationDistance = 683,
        StrategicNumberNameSnTargetEvaluationHitpoints = 684,
        StrategicNumberNameSnTargetEvaluationDamageCapability = 685,
        StrategicNumberNameSnTargetEvaluationKills = 686,
        StrategicNumberNameSnTargetEvaluationAllyProximity = 687,
        StrategicNumberNameSnTargetEvaluationRof = 688,
        StrategicNumberNameSnTargetEvaluationRandomness = 689,
        StrategicNumberNameSnCampMaxDistance = 690,
        StrategicNumberNameSnMillMaxDistance = 691,
        StrategicNumberNameSnTargetEvaluationAttackAttempts = 692,
        StrategicNumberNameSnTargetEvaluationRange = 693,
        StrategicNumberNameSnDefendOverlapDistance = 694,
        StrategicNumberNameSnScaleMinimumAttackGroupSize = 695,
        StrategicNumberNameSnScaleMaximumAttackGroupSize = 696,
        StrategicNumberNameSnAttackGroupSizeRandomness = 697,
        StrategicNumberNameSnScalingFrequency = 698,
        StrategicNumberNameSnMaximumGaiaAttackResponse = 699,
        StrategicNumberNameSnBuildFrequency = 700,
        StrategicNumberNameSnAttackSeparationTimeRandomness = 701,
        StrategicNumberNameSnAttackIntelligence = 702,
        StrategicNumberNameSnInitialAttackDelay = 703,
        StrategicNumberNameSnSaveScenarioInformation = 704,
        StrategicNumberNameSnSpecialAttackType1 = 705,
        StrategicNumberNameSnSpecialAttackInfluence1 = 706,
        StrategicNumberNameSnMinimumWaterBodySizeForDock = 707,
        StrategicNumberNameSnNumberBuildAttemptsBeforeSkip = 708,
        StrategicNumberNameSnMaxSkipsPerAttempt = 709,
        StrategicNumberNameSnFoodGathererPercentage = 710,
        StrategicNumberNameSnGoldGathererPercentage = 711,
        StrategicNumberNameSnStoneGathererPercentage = 712,
        StrategicNumberNameSnWoodGathererPercentage = 713,
        StrategicNumberNameSnTargetEvaluationContinent = 714,
        StrategicNumberNameSnTargetEvaluationSiegeWeapon = 715,
        StrategicNumberNameSnGroupLeaderDefenseDistance = 716,
        StrategicNumberNameSnInitialAttackDelayType = 717,
        StrategicNumberNameSnBlotExplorationMap = 718,
        StrategicNumberNameSnBlotSize = 719,
        StrategicNumberNameSnIntelligentGathering = 720,
        StrategicNumberNameSnTaskUngroupedSoldiers = 721,
        StrategicNumberNameSnTargetEvaluationBoat = 722,
        StrategicNumberNameSnNumberEnemyObjectsRequired = 723,
        StrategicNumberNameSnNumberMaxSkipCycles = 724,
        StrategicNumberNameSnRetaskGatherAmount = 725,
        StrategicNumberNameSnMaxRetaskGatherAmount = 726,
        StrategicNumberNameSnMaxBuildPlanGathererPercentage = 727,
        StrategicNumberNameSnFoodDropsiteDistance = 728,
        StrategicNumberNameSnWoodDropsiteDistance = 729,
        StrategicNumberNameSnStoneDropsiteDistance = 730,
        StrategicNumberNameSnGoldDropsiteDistance = 731,
        StrategicNumberNameSnInitialExplorationRequired = 732,
        StrategicNumberNameSnRandomPlacementFactor = 733,
        StrategicNumberNameSnRequiredForestTiles = 734,
        StrategicNumberNameSnAttackDiplomacyImpact = 735,
        StrategicNumberNameSnPercentHalfExploration = 736,
        StrategicNumberNameSnTargetEvaluationTimeKillRatio = 737,
        StrategicNumberNameSnTargetEvaluationInProgress = 738,
        StrategicNumberNameSnAttackWinningPlayer = 739,
        StrategicNumberNameSnCoopShareInformation = 740,
        StrategicNumberNameSnAttackWinningPlayerFactor = 741,
        StrategicNumberNameSnCoopShareAttacking = 742,
        StrategicNumberNameSnCoopShareAttackingInterval = 743,
        StrategicNumberNameSnPercentageExploreExterminators = 744,
        StrategicNumberNameSnTrackPlayerHistory = 745,
        StrategicNumberNameSnMinimumDropsiteBuffer = 746,
        StrategicNumberNameSnUseByTypeMaxGathering = 747,
        StrategicNumberNameSnMinimumBoarHuntGroupSize = 748,
        StrategicNumberNameSnMinimumAmountForTrading = 749,
        StrategicNumberNameSnEasiestReactionPercentage = 750,
        StrategicNumberNameSnEasierReactionPercentage = 751,
        StrategicNumberNameSnHitsBeforeAllianceChange = 752,
        StrategicNumberNameSnAllowCivilianDefense = 753,
        StrategicNumberNameSnNumberForwardBuilders = 754,
        StrategicNumberNameSnPercentAttackSoldiers = 755,
        StrategicNumberNameSnPercentAttackBoats = 756,
        StrategicNumberNameSnDoNotScaleForDifficultyLevel = 757,
        StrategicNumberNameSnGroupFormDistance = 758,
        StrategicNumberNameSnIgnoreAttackGroupUnderAttack = 759,
        StrategicNumberNameSnGatherDefenseUnits = 760,
        StrategicNumberNameSnMaximumWoodDropDistance = 761,
        StrategicNumberNameSnMaximumFoodDropDistance = 762,
        StrategicNumberNameSnMaximumHuntDropDistance = 763,
        StrategicNumberNameSnMaximumFishBoatDropDistance = 764,
        StrategicNumberNameSnMaximumGoldDropDistance = 765,
        StrategicNumberNameSnMaximumStoneDropDistance = 766,
        StrategicNumberNameSnGatherIdleSoldiersAtCenter = 767,
        StrategicNumberNameSnGarrisonRams = 768,
        Taunt = 769,
        TauntDetected = 770,
        TauntUsingRange = 771,
        TimerTriggered = 772,
        TownUnderAttack = 773,
        Train = 774,
        TributeToPlayer = 775,
        Trueval = 776,
        UnitArbalest = 777,
        UnitArcher = 778,
        UnitCavalryArcher = 779,
        UnitCrossbowman = 780,
        UnitEliteSkirmisher = 781,
        UnitHandCannoneer = 782,
        UnitHeavyCavalryArcher = 783,
        UnitSkirmisher = 784,
        UnitChampion = 785,
        UnitEagleWarrior = 786,
        UnitEliteEagleWarrior = 787,
        UnitHalberdier = 788,
        UnitLongSwordsman = 789,
        UnitManAtArms = 790,
        UnitMilitiaman = 791,
        UnitPikeman = 792,
        UnitSpearman = 793,
        UnitTwoHandedSwordsman = 794,
        UnitBerserk = 795,
        UnitCataphract = 796,
        UnitChuKoNu = 797,
        UnitConquistador = 798,
        UnitEliteBerserk = 799,
        UnitEliteCataphract = 800,
        UnitEliteChuKoNu = 801,
        UnitEliteConquistador = 802,
        UnitEliteHuskarl = 803,
        UnitEliteJaguarWarrior = 804,
        UnitEliteJanissary = 805,
        UnitEliteLongbowman = 806,
        UnitEliteMameluke = 807,
        UnitEliteMangudai = 808,
        UnitElitePlumedArcher = 809,
        UnitEliteSamurai = 810,
        UnitEliteTarkan = 811,
        UnitEliteTeutonicKnight = 812,
        UnitEliteThrowingAxeman = 813,
        UnitEliteWarElephant = 814,
        UnitEliteWarWagon = 815,
        UnitEliteWoadRaider = 816,
        UnitHuskarl = 817,
        UnitJaguarWarrior = 818,
        UnitJanissary = 819,
        UnitLongbowman = 820,
        UnitMameluke = 821,
        UnitMangudai = 822,
        UnitPetard = 823,
        UnitPlumedArcher = 824,
        UnitSamurai = 825,
        UnitTarkan = 826,
        UnitTeutonicKnight = 827,
        UnitThrowingAxeman = 828,
        UnitTrebuchet = 829,
        UnitWarElephant = 830,
        UnitWarWagon = 831,
        UnitWoadRaider = 832,
        UnitCannonGalleon = 833,
        UnitDemolitionShip = 834,
        UnitEliteCannonGalleon = 835,
        UnitEliteLongboat = 836,
        UnitEliteTurtleShip = 837,
        UnitFastFireShip = 838,
        UnitFireShip = 839,
        UnitFishingShip = 840,
        UnitGalleon = 841,
        UnitGalley = 842,
        UnitHeavyDemolitionShip = 843,
        UnitLongboat = 844,
        UnitTradeCog = 845,
        UnitTransportShip = 846,
        UnitTurtleShip = 847,
        UnitWarGalley = 848,
        UnitTradeCart = 849,
        UnitMissionary = 850,
        UnitMonk = 851,
        UnitBatteringRam = 852,
        UnitBombardCannon = 853,
        UnitCappedRam = 854,
        UnitHeavyScorpion = 855,
        UnitMangonel = 856,
        UnitOnager = 857,
        UnitScorpion = 858,
        UnitSiegeOnager = 859,
        UnitSiegeRam = 860,
        UnitCamel = 861,
        UnitCavalier = 862,
        UnitHeavyCamel = 863,
        UnitHussar = 864,
        UnitKnight = 865,
        UnitLightCavalry = 866,
        UnitPaladin = 867,
        UnitScoutCavalry = 868,
        UnitVillager = 869,
        UnitArcherLine = 870,
        UnitCavalryArcherLine = 871,
        UnitSkirmisherLine = 872,
        UnitEagleWarriorLine = 873,
        UnitMilitiamanLine = 874,
        UnitSpearmanLine = 875,
        UnitBerserkLine = 876,
        UnitCataphractLine = 877,
        UnitChuKoNuLine = 878,
        UnitConquistadorLine = 879,
        UnitHuskarlLine = 880,
        UnitJaguarWarriorLine = 881,
        UnitJanissaryLine = 882,
        UnitLongbowmanLine = 883,
        UnitMamelukeLine = 884,
        UnitMangudaiLine = 885,
        UnitPlumedArcherLine = 886,
        UnitSamuraiLine = 887,
        UnitTarkanLine = 888,
        UnitTeutonicKnightLine = 889,
        UnitThrowingAxemanLine = 890,
        UnitWarElephantLine = 891,
        UnitWarWagonLine = 892,
        UnitWoadRaiderLine = 893,
        UnitCannonGalleonLine = 894,
        UnitDemolitionShipLine = 895,
        UnitFireShipLine = 896,
        UnitGalleyLine = 897,
        UnitLongboatLine = 898,
        UnitTurtleShipLine = 899,
        UnitBatteringRamLine = 900,
        UnitMangonelLine = 901,
        UnitScorpionLine = 902,
        UnitCamelLine = 903,
        UnitKnightLine = 904,
        UnitScoutCavalryLine = 905,
        UnitMyEliteUniqueUnit = 906,
        UnitMyUniqueUnit = 907,
        UnitMyUniqueUnitLine = 908,
        UnitAvailable = 909,
        UnitCount = 910,
        UnitCountTotal = 911,
        UnitTypeCount = 912,
        UnitTypeCountTotal = 913,
        VictoryCondition = 914,
        VictoryConditionNameStandard = 915,
        VictoryConditionNameConquest = 916,
        VictoryConditionNameTimeLimit = 917,
        VictoryConditionNameScore = 918,
        VictoryConditionNameCustom = 919,
        WallCompletedPercentage = 920,
        WallInvisiblePercentage = 921,
        WallTypeFortifiedWall = 922,
        WallTypePalisadeWall = 923,
        WallTypeStoneWall = 924,
        WallTypeStoneWallLine = 925,
        WarboatCount = 926,
        WoodAmount = 927
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef short token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ActionType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ActionType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Age&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Age& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Building&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Building& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Civ&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Civ& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Commodity&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Commodity& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, DifficultyLevel&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DifficultyLevel& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, DifficultyParameter&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DifficultyParameter& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, DiplomaticStance&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DiplomaticStance& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Fact&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Fact& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, MapSizeType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const MapSizeType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, MapTypeName&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const MapTypeName& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, PlayerNumberType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const PlayerNumberType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, RelOp&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const RelOp& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ResearchItem&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ResearchItem& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, StartingResourcesType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const StartingResourcesType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, StrategicNumberName&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const StrategicNumberName& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unit&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unit& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VictoryConditionName&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VictoryConditionName& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, WallType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const WallType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ai::Action>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ai::Action>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ai::AiRule>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ai::AiRule>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<ai::Condition>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<ai::Condition>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::shared_ptr<ai::Action>>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<ai::Action>>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::shared_ptr<ai::Condition>>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<ai::Condition>>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_number_type yytype = this->type_get ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yytype)
        {
       default:
          break;
        }

        // Type destructor.
switch (yytype)
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
        value.template destroy< ActionType > ();
        break;

      case 682: // age
        value.template destroy< Age > ();
        break;

      case 683: // building
        value.template destroy< Building > ();
        break;

      case 684: // civ
        value.template destroy< Civ > ();
        break;

      case 685: // commodity
        value.template destroy< Commodity > ();
        break;

      case 686: // difficultylevel
        value.template destroy< DifficultyLevel > ();
        break;

      case 687: // difficultyparameter
        value.template destroy< DifficultyParameter > ();
        break;

      case 688: // diplomaticstance
        value.template destroy< DiplomaticStance > ();
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
        value.template destroy< Fact > ();
        break;

      case 689: // mapsizetype
        value.template destroy< MapSizeType > ();
        break;

      case 690: // maptypename
        value.template destroy< MapTypeName > ();
        break;

      case 691: // playernumbertype
        value.template destroy< PlayerNumberType > ();
        break;

      case 692: // relop
        value.template destroy< RelOp > ();
        break;

      case 693: // researchitem
        value.template destroy< ResearchItem > ();
        break;

      case 694: // startingresourcestype
        value.template destroy< StartingResourcesType > ();
        break;

      case 695: // strategicnumbername
        value.template destroy< StrategicNumberName > ();
        break;

      case 696: // unit
        value.template destroy< Unit > ();
        break;

      case 697: // victoryconditionname
        value.template destroy< VictoryConditionName > ();
        break;

      case 698: // walltype
        value.template destroy< WallType > ();
        break;

      case 3: // Number
        value.template destroy< int > ();
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
        value.template destroy< std::shared_ptr<ai::Action> > ();
        break;

      case 676: // rule
        value.template destroy< std::shared_ptr<ai::AiRule> > ();
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
        value.template destroy< std::shared_ptr<ai::Condition> > ();
        break;

      case 4: // String
      case 5: // SymbolName
        value.template destroy< std::string > ();
        break;

      case 680: // actions
        value.template destroy< std::vector<std::shared_ptr<ai::Action>> > ();
        break;

      case 677: // conditions
        value.template destroy< std::vector<std::shared_ptr<ai::Condition>> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {
      /// Superclass.
      typedef basic_symbol<by_type> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YY_ASSERT (tok == token::ScriptEnd || tok == token::OpenParen || tok ==
                token::CloseParen || tok == token::RuleStart || tok ==
                token::ConditionActionSeparator || tok == token::Not || tok ==
                token::Or || tok == token::LoadIfDefined || tok == token::Else
                || tok == token::EndIf || tok == token::Space || tok ==
                token::NewLine || tok == token::AgeDarkAge || tok ==
                token::AgeFeudalAge || tok == token::AgeCastleAge || tok ==
                token::AgeImperialAge || tok == token::AgePostImperialAge ||
                tok == token::BuildingArcheryRange || tok ==
                token::BuildingBarracks || tok == token::BuildingBlacksmith ||
                tok == token::BuildingBombardTower || tok ==
                token::BuildingCastle || tok == token::BuildingDock || tok ==
                token::BuildingFarm || tok == token::BuildingFishTrap || tok ==
                token::BuildingGuardTower || tok == token::BuildingHouse || tok
                == token::BuildingKeep || tok == token::BuildingLumberCamp ||
                tok == token::BuildingMarket || tok == token::BuildingMill ||
                tok == token::BuildingMiningCamp || tok ==
                token::BuildingMonastery || tok == token::BuildingOutpost ||
                tok == token::BuildingSiegeWorkshop || tok ==
                token::BuildingStable || tok == token::BuildingTownCenter ||
                tok == token::BuildingUniversity || tok ==
                token::BuildingWatchTower || tok == token::BuildingWonder ||
                tok == token::BuildingWatchTowerLine || tok == token::CivBriton
                || tok == token::CivByzantine || tok == token::CivCeltic || tok
                == token::CivChinese || tok == token::CivFrankish || tok ==
                token::CivGothic || tok == token::CivJapanese || tok ==
                token::CivMongol || tok == token::CivPersian || tok ==
                token::CivSaracen || tok == token::CivTeutonic || tok ==
                token::CivTurkish || tok == token::CivViking || tok ==
                token::CivMyCiv || tok == token::CommodityFood || tok ==
                token::CommodityStone || tok == token::CommodityWood || tok ==
                token::CommodityGold || tok == token::DifficultyLevelEasiest ||
                tok == token::DifficultyLevelEasy || tok ==
                token::DifficultyLevelModerate || tok ==
                token::DifficultyLevelHard || tok ==
                token::DifficultyLevelHardest || tok ==
                token::DifficultyParameterAbilityToDodgeMissiles || tok ==
                token::DifficultyParameterAbilityToMaintainDistance || tok ==
                token::DiplomaticStanceAlly || tok ==
                token::DiplomaticStanceNeutral || tok ==
                token::DiplomaticStanceEnemy || tok == token::MapSizeTypeTiny
                || tok == token::MapSizeTypeSmall || tok ==
                token::MapSizeTypeMedium || tok == token::MapSizeTypeNormal ||
                tok == token::MapSizeTypeLarge || tok ==
                token::MapSizeTypeGiant || tok == token::MapTypeNameArabia ||
                tok == token::MapTypeNameArchipelago || tok ==
                token::MapTypeNameBaltic || tok ==
                token::MapTypeNameBlackForest || tok ==
                token::MapTypeNameCoastal || tok ==
                token::MapTypeNameContinental || tok ==
                token::MapTypeNameCraterLake || tok ==
                token::MapTypeNameFortress || tok == token::MapTypeNameGoldRush
                || tok == token::MapTypeNameHighland || tok ==
                token::MapTypeNameIslands || tok ==
                token::MapTypeNameMediterranean || tok ==
                token::MapTypeNameMigration || tok == token::MapTypeNameRivers
                || tok == token::MapTypeNameTeamIslands || tok ==
                token::MapTypeNameScenarioMap || tok ==
                token::PlayerNumberTypeAnyAlly || tok ==
                token::PlayerNumberTypeAnyComputer || tok ==
                token::PlayerNumberTypeAnyComputerAlly || tok ==
                token::PlayerNumberTypeAnyComputerEnemy || tok ==
                token::PlayerNumberTypeAnyComputerNeutral || tok ==
                token::PlayerNumberTypeAnyEnemy || tok ==
                token::PlayerNumberTypeAnyHuman || tok ==
                token::PlayerNumberTypeAnyHumanAlly || tok ==
                token::PlayerNumberTypeAnyHumanEnemy || tok ==
                token::PlayerNumberTypeAnyHumanNeutral || tok ==
                token::PlayerNumberTypeAnyNeutral || tok ==
                token::PlayerNumberTypeEveryAlly || tok ==
                token::PlayerNumberTypeEveryComputer || tok ==
                token::PlayerNumberTypeEveryEnemy || tok ==
                token::PlayerNumberTypeEveryHuman || tok ==
                token::PlayerNumberTypeEveryNeutral || tok ==
                token::PlayerNumberTypeMyPlayerNumber || tok ==
                token::RelOpLessThan || tok == token::RelOpLessOrEqual || tok
                == token::RelOpGreaterThan || tok == token::RelOpGreaterOrEqual
                || tok == token::RelOpEqual || tok == token::RelOpNotEqual ||
                tok == token::ResearchItemRiArbalest || tok ==
                token::ResearchItemRiCrossbow || tok ==
                token::ResearchItemRiEliteSkirmisher || tok ==
                token::ResearchItemRiHandCannon || tok ==
                token::ResearchItemRiHeavyCavalryArcher || tok ==
                token::ResearchItemRiChampion || tok ==
                token::ResearchItemRiEliteEagleWarrior || tok ==
                token::ResearchItemRiHalberdier || tok ==
                token::ResearchItemRiLongSwordsman || tok ==
                token::ResearchItemRiManAtArms || tok ==
                token::ResearchItemRiParthianTactics || tok ==
                token::ResearchItemRiPikeman || tok ==
                token::ResearchItemRiSquires || tok ==
                token::ResearchItemRiThumbRing || tok ==
                token::ResearchItemRiTracking || tok ==
                token::ResearchItemRiTwoHandedSwordsman || tok ==
                token::ResearchItemRiBlastFurnace || tok ==
                token::ResearchItemRiBodkinArrow || tok ==
                token::ResearchItemRiBracer || tok ==
                token::ResearchItemRiChainBarding || tok ==
                token::ResearchItemRiChainMail || tok ==
                token::ResearchItemRiFletching || tok ==
                token::ResearchItemRiForging || tok ==
                token::ResearchItemRiIronCasting || tok ==
                token::ResearchItemRiLeatherArcherArmor || tok ==
                token::ResearchItemRiPaddedArcherArmor || tok ==
                token::ResearchItemRiPlateBarding || tok ==
                token::ResearchItemRiPlateMail || tok ==
                token::ResearchItemRiRingArcherArmor || tok ==
                token::ResearchItemRiScaleBarding || tok ==
                token::ResearchItemRiScaleMail || tok ==
                token::ResearchItemRiConscription || tok ==
                token::ResearchItemRiHoardings || tok ==
                token::ResearchItemRiSappers || tok ==
                token::ResearchItemRiEliteBerserk || tok ==
                token::ResearchItemRiEliteCataphract || tok ==
                token::ResearchItemRiEliteChuKoNu || tok ==
                token::ResearchItemRiEliteHuskarl || tok ==
                token::ResearchItemRiEliteJanissary || tok ==
                token::ResearchItemRiEliteLongbowman || tok ==
                token::ResearchItemRiEliteMameluke || tok ==
                token::ResearchItemRiEliteMangudai || tok ==
                token::ResearchItemRiEliteSamurai || tok ==
                token::ResearchItemRiEliteTeutonicKnight || tok ==
                token::ResearchItemRiEliteThrowingAxeman || tok ==
                token::ResearchItemRiEliteWarElephant || tok ==
                token::ResearchItemRiEliteWoadRaider || tok ==
                token::ResearchItemRiMyUniqueEliteUnit || tok ==
                token::ResearchItemRiMyUniqueResearch || tok ==
                token::ResearchItemRiCannonGalleon || tok ==
                token::ResearchItemRiCareening || tok ==
                token::ResearchItemRiDeckGuns || tok ==
                token::ResearchItemRiDryDock || tok ==
                token::ResearchItemRiEliteLongboat || tok ==
                token::ResearchItemRiFastFireShip || tok ==
                token::ResearchItemRiGalleon || tok ==
                token::ResearchItemRiHeavyDemolitionShip || tok ==
                token::ResearchItemRiShipwright || tok ==
                token::ResearchItemRiWarGalley || tok ==
                token::ResearchItemRiBowSaw || tok ==
                token::ResearchItemRiDoubleBitAxe || tok ==
                token::ResearchItemRiTwoManSaw || tok ==
                token::ResearchItemRiBanking || tok ==
                token::ResearchItemRiCaravan || tok ==
                token::ResearchItemRiCartography || tok ==
                token::ResearchItemRiCoinage || tok ==
                token::ResearchItemRiGuilds || tok ==
                token::ResearchItemRiCropRotation || tok ==
                token::ResearchItemRiHeavyPlow || tok ==
                token::ResearchItemRiHorseCollar || tok ==
                token::ResearchItemRiGoldMining || tok ==
                token::ResearchItemRiGoldShaftMining || tok ==
                token::ResearchItemRiStoneMining || tok ==
                token::ResearchItemRiStoneShaftMining || tok ==
                token::ResearchItemRiAtonement || tok ==
                token::ResearchItemRiBlockPrinting || tok ==
                token::ResearchItemRiFaith || tok ==
                token::ResearchItemRiFervor || tok ==
                token::ResearchItemRiHerbalMedicine || tok ==
                token::ResearchItemRiHeresy || tok ==
                token::ResearchItemRiIllumination || tok ==
                token::ResearchItemRiRedemption || tok ==
                token::ResearchItemRiSanctity || tok ==
                token::ResearchItemRiTheocracy || tok ==
                token::ResearchItemRiBombardCannon || tok ==
                token::ResearchItemRiCappedRam || tok ==
                token::ResearchItemRiHeavyScorpion || tok ==
                token::ResearchItemRiOnager || tok ==
                token::ResearchItemRiScorpion || tok ==
                token::ResearchItemRiSiegeOnager || tok ==
                token::ResearchItemRiSiegeRam || tok ==
                token::ResearchItemRiBloodlines || tok ==
                token::ResearchItemRiCavalier || tok ==
                token::ResearchItemRiHeavyCamel || tok ==
                token::ResearchItemRiHusbandry || tok ==
                token::ResearchItemRiHussar || tok ==
                token::ResearchItemRiLightCavalry || tok ==
                token::ResearchItemRiPaladin || tok ==
                token::ResearchItemRiHandCart || tok ==
                token::ResearchItemRiLoom || tok ==
                token::ResearchItemRiTownPatrol || tok ==
                token::ResearchItemRiTownWatch || tok ==
                token::ResearchItemRiWheelBarrow || tok ==
                token::ResearchItemRiArchitecture || tok ==
                token::ResearchItemRiBallistics || tok ==
                token::ResearchItemRiBombardTower || tok ==
                token::ResearchItemRiChemistry || tok ==
                token::ResearchItemRiFortifiedWall || tok ==
                token::ResearchItemRiGuardTower || tok ==
                token::ResearchItemRiHeatedShot || tok ==
                token::ResearchItemRiKeep || tok ==
                token::ResearchItemRiMasonry || tok ==
                token::ResearchItemRiMurderHoles || tok ==
                token::ResearchItemRiSiegeEngineers || tok ==
                token::ResearchItemRiStonecutting || tok ==
                token::ResearchItemMyUniqueUnitUpgrade || tok ==
                token::ResearchItemMyUniqueResearch || tok ==
                token::StartingResourcesTypeLowResources || tok ==
                token::StartingResourcesTypeMediumResources || tok ==
                token::StartingResourcesTypeHighResources || tok ==
                token::StrategicNumberNameSnPercentCivilianExplorers || tok ==
                token::StrategicNumberNameSnPercentCivilianBuilders || tok ==
                token::StrategicNumberNameSnPercentCivilianGatherers || tok ==
                token::StrategicNumberNameSnCapCivilianExplorers || tok ==
                token::StrategicNumberNameSnCapCivilianBuilders || tok ==
                token::StrategicNumberNameSnCapCivilianGatherers || tok ==
                token::StrategicNumberNameSnMinimumAttackGroupSize || tok ==
                token::StrategicNumberNameSnTotalNumberExplorers || tok ==
                token::StrategicNumberNameSnPercentEnemySightedResponse || tok
                == token::StrategicNumberNameSnEnemySightedResponseDistance ||
                tok == token::StrategicNumberNameSnSentryDistance || tok ==
                token::StrategicNumberNameSnRelicReturnDistance || tok ==
                token::StrategicNumberNameSnMinimumDefendGroupSize || tok ==
                token::StrategicNumberNameSnMaximumAttackGroupSize || tok ==
                token::StrategicNumberNameSnMaximumDefendGroupSize || tok ==
                token::StrategicNumberNameSnMinimumPeaceLikeLevel || tok ==
                token::StrategicNumberNameSnPercentExplorationRequired || tok
                == token::StrategicNumberNameSnZeroPriorityDistance || tok ==
                token::StrategicNumberNameSnMinimumCivilianExplorers || tok ==
                token::StrategicNumberNameSnNumberAttackGroups || tok ==
                token::StrategicNumberNameSnNumberDefendGroups || tok ==
                token::StrategicNumberNameSnAttackGroupGatherSpacing || tok ==
                token::StrategicNumberNameSnNumberExploreGroups || tok ==
                token::StrategicNumberNameSnMinimumExploreGroupSize || tok ==
                token::StrategicNumberNameSnMaximumExploreGroupSize || tok ==
                token::StrategicNumberNameSnGoldDefendPriority || tok ==
                token::StrategicNumberNameSnStoneDefendPriority || tok ==
                token::StrategicNumberNameSnForageDefendPriority || tok ==
                token::StrategicNumberNameSnRelicDefendPriority || tok ==
                token::StrategicNumberNameSnTownDefendPriority || tok ==
                token::StrategicNumberNameSnDefenseDistance || tok ==
                token::StrategicNumberNameSnNumberBoatAttackGroups || tok ==
                token::StrategicNumberNameSnMinimumBoatAttackGroupSize || tok
                == token::StrategicNumberNameSnMaximumBoatAttackGroupSize ||
                tok == token::StrategicNumberNameSnNumberBoatExploreGroups ||
                tok == token::StrategicNumberNameSnMinimumBoatExploreGroupSize
                || tok ==
                token::StrategicNumberNameSnMaximumBoatExploreGroupSize || tok
                == token::StrategicNumberNameSnNumberBoatDefendGroups || tok ==
                token::StrategicNumberNameSnMinimumBoatDefendGroupSize || tok
                == token::StrategicNumberNameSnMaximumBoatDefendGroupSize ||
                tok == token::StrategicNumberNameSnDockDefendPriority || tok ==
                token::StrategicNumberNameSnSentryDistanceVariation || tok ==
                token::StrategicNumberNameSnMinimumTownSize || tok ==
                token::StrategicNumberNameSnMaximumTownSize || tok ==
                token::StrategicNumberNameSnGroupCommanderSelectionMethod ||
                tok == token::StrategicNumberNameSnConsecutiveIdleUnitLimit ||
                tok == token::StrategicNumberNameSnTargetEvaluationDistance ||
                tok == token::StrategicNumberNameSnTargetEvaluationHitpoints ||
                tok ==
                token::StrategicNumberNameSnTargetEvaluationDamageCapability ||
                tok == token::StrategicNumberNameSnTargetEvaluationKills || tok
                == token::StrategicNumberNameSnTargetEvaluationAllyProximity ||
                tok == token::StrategicNumberNameSnTargetEvaluationRof || tok
                == token::StrategicNumberNameSnTargetEvaluationRandomness ||
                tok == token::StrategicNumberNameSnCampMaxDistance || tok ==
                token::StrategicNumberNameSnMillMaxDistance || tok ==
                token::StrategicNumberNameSnTargetEvaluationAttackAttempts ||
                tok == token::StrategicNumberNameSnTargetEvaluationRange || tok
                == token::StrategicNumberNameSnDefendOverlapDistance || tok ==
                token::StrategicNumberNameSnScaleMinimumAttackGroupSize || tok
                == token::StrategicNumberNameSnScaleMaximumAttackGroupSize ||
                tok == token::StrategicNumberNameSnAttackGroupSizeRandomness ||
                tok == token::StrategicNumberNameSnScalingFrequency || tok ==
                token::StrategicNumberNameSnMaximumGaiaAttackResponse || tok ==
                token::StrategicNumberNameSnBuildFrequency || tok ==
                token::StrategicNumberNameSnAttackSeparationTimeRandomness ||
                tok == token::StrategicNumberNameSnAttackIntelligence || tok ==
                token::StrategicNumberNameSnInitialAttackDelay || tok ==
                token::StrategicNumberNameSnSaveScenarioInformation || tok ==
                token::StrategicNumberNameSnSpecialAttackType1 || tok ==
                token::StrategicNumberNameSnSpecialAttackInfluence1 || tok ==
                token::StrategicNumberNameSnMinimumWaterBodySizeForDock || tok
                == token::StrategicNumberNameSnNumberBuildAttemptsBeforeSkip ||
                tok == token::StrategicNumberNameSnMaxSkipsPerAttempt || tok ==
                token::StrategicNumberNameSnFoodGathererPercentage || tok ==
                token::StrategicNumberNameSnGoldGathererPercentage || tok ==
                token::StrategicNumberNameSnStoneGathererPercentage || tok ==
                token::StrategicNumberNameSnWoodGathererPercentage || tok ==
                token::StrategicNumberNameSnTargetEvaluationContinent || tok ==
                token::StrategicNumberNameSnTargetEvaluationSiegeWeapon || tok
                == token::StrategicNumberNameSnGroupLeaderDefenseDistance ||
                tok == token::StrategicNumberNameSnInitialAttackDelayType ||
                tok == token::StrategicNumberNameSnBlotExplorationMap || tok ==
                token::StrategicNumberNameSnBlotSize || tok ==
                token::StrategicNumberNameSnIntelligentGathering || tok ==
                token::StrategicNumberNameSnTaskUngroupedSoldiers || tok ==
                token::StrategicNumberNameSnTargetEvaluationBoat || tok ==
                token::StrategicNumberNameSnNumberEnemyObjectsRequired || tok
                == token::StrategicNumberNameSnNumberMaxSkipCycles || tok ==
                token::StrategicNumberNameSnRetaskGatherAmount || tok ==
                token::StrategicNumberNameSnMaxRetaskGatherAmount || tok ==
                token::StrategicNumberNameSnMaxBuildPlanGathererPercentage ||
                tok == token::StrategicNumberNameSnFoodDropsiteDistance || tok
                == token::StrategicNumberNameSnWoodDropsiteDistance || tok ==
                token::StrategicNumberNameSnStoneDropsiteDistance || tok ==
                token::StrategicNumberNameSnGoldDropsiteDistance || tok ==
                token::StrategicNumberNameSnInitialExplorationRequired || tok
                == token::StrategicNumberNameSnRandomPlacementFactor || tok ==
                token::StrategicNumberNameSnRequiredForestTiles || tok ==
                token::StrategicNumberNameSnAttackDiplomacyImpact || tok ==
                token::StrategicNumberNameSnPercentHalfExploration || tok ==
                token::StrategicNumberNameSnTargetEvaluationTimeKillRatio ||
                tok == token::StrategicNumberNameSnTargetEvaluationInProgress
                || tok == token::StrategicNumberNameSnAttackWinningPlayer ||
                tok == token::StrategicNumberNameSnCoopShareInformation || tok
                == token::StrategicNumberNameSnAttackWinningPlayerFactor || tok
                == token::StrategicNumberNameSnCoopShareAttacking || tok ==
                token::StrategicNumberNameSnCoopShareAttackingInterval || tok
                == token::StrategicNumberNameSnPercentageExploreExterminators
                || tok == token::StrategicNumberNameSnTrackPlayerHistory || tok
                == token::StrategicNumberNameSnMinimumDropsiteBuffer || tok ==
                token::StrategicNumberNameSnUseByTypeMaxGathering || tok ==
                token::StrategicNumberNameSnMinimumBoarHuntGroupSize || tok ==
                token::StrategicNumberNameSnMinimumAmountForTrading || tok ==
                token::StrategicNumberNameSnEasiestReactionPercentage || tok ==
                token::StrategicNumberNameSnEasierReactionPercentage || tok ==
                token::StrategicNumberNameSnHitsBeforeAllianceChange || tok ==
                token::StrategicNumberNameSnAllowCivilianDefense || tok ==
                token::StrategicNumberNameSnNumberForwardBuilders || tok ==
                token::StrategicNumberNameSnPercentAttackSoldiers || tok ==
                token::StrategicNumberNameSnPercentAttackBoats || tok ==
                token::StrategicNumberNameSnDoNotScaleForDifficultyLevel || tok
                == token::StrategicNumberNameSnGroupFormDistance || tok ==
                token::StrategicNumberNameSnIgnoreAttackGroupUnderAttack || tok
                == token::StrategicNumberNameSnGatherDefenseUnits || tok ==
                token::StrategicNumberNameSnMaximumWoodDropDistance || tok ==
                token::StrategicNumberNameSnMaximumFoodDropDistance || tok ==
                token::StrategicNumberNameSnMaximumHuntDropDistance || tok ==
                token::StrategicNumberNameSnMaximumFishBoatDropDistance || tok
                == token::StrategicNumberNameSnMaximumGoldDropDistance || tok
                == token::StrategicNumberNameSnMaximumStoneDropDistance || tok
                == token::StrategicNumberNameSnGatherIdleSoldiersAtCenter ||
                tok == token::StrategicNumberNameSnGarrisonRams || tok ==
                token::UnitArbalest || tok == token::UnitArcher || tok ==
                token::UnitCavalryArcher || tok == token::UnitCrossbowman ||
                tok == token::UnitEliteSkirmisher || tok ==
                token::UnitHandCannoneer || tok ==
                token::UnitHeavyCavalryArcher || tok == token::UnitSkirmisher
                || tok == token::UnitChampion || tok == token::UnitEagleWarrior
                || tok == token::UnitEliteEagleWarrior || tok ==
                token::UnitHalberdier || tok == token::UnitLongSwordsman || tok
                == token::UnitManAtArms || tok == token::UnitMilitiaman || tok
                == token::UnitPikeman || tok == token::UnitSpearman || tok ==
                token::UnitTwoHandedSwordsman || tok == token::UnitBerserk ||
                tok == token::UnitCataphract || tok == token::UnitChuKoNu ||
                tok == token::UnitConquistador || tok ==
                token::UnitEliteBerserk || tok == token::UnitEliteCataphract ||
                tok == token::UnitEliteChuKoNu || tok ==
                token::UnitEliteConquistador || tok == token::UnitEliteHuskarl
                || tok == token::UnitEliteJaguarWarrior || tok ==
                token::UnitEliteJanissary || tok == token::UnitEliteLongbowman
                || tok == token::UnitEliteMameluke || tok ==
                token::UnitEliteMangudai || tok == token::UnitElitePlumedArcher
                || tok == token::UnitEliteSamurai || tok ==
                token::UnitEliteTarkan || tok == token::UnitEliteTeutonicKnight
                || tok == token::UnitEliteThrowingAxeman || tok ==
                token::UnitEliteWarElephant || tok == token::UnitEliteWarWagon
                || tok == token::UnitEliteWoadRaider || tok ==
                token::UnitHuskarl || tok == token::UnitJaguarWarrior || tok ==
                token::UnitJanissary || tok == token::UnitLongbowman || tok ==
                token::UnitMameluke || tok == token::UnitMangudai || tok ==
                token::UnitPetard || tok == token::UnitPlumedArcher || tok ==
                token::UnitSamurai || tok == token::UnitTarkan || tok ==
                token::UnitTeutonicKnight || tok == token::UnitThrowingAxeman
                || tok == token::UnitTrebuchet || tok == token::UnitWarElephant
                || tok == token::UnitWarWagon || tok == token::UnitWoadRaider
                || tok == token::UnitCannonGalleon || tok ==
                token::UnitDemolitionShip || tok ==
                token::UnitEliteCannonGalleon || tok ==
                token::UnitEliteLongboat || tok == token::UnitEliteTurtleShip
                || tok == token::UnitFastFireShip || tok == token::UnitFireShip
                || tok == token::UnitFishingShip || tok == token::UnitGalleon
                || tok == token::UnitGalley || tok ==
                token::UnitHeavyDemolitionShip || tok == token::UnitLongboat ||
                tok == token::UnitTradeCog || tok == token::UnitTransportShip
                || tok == token::UnitTurtleShip || tok == token::UnitWarGalley
                || tok == token::UnitTradeCart || tok == token::UnitMissionary
                || tok == token::UnitMonk || tok == token::UnitBatteringRam ||
                tok == token::UnitBombardCannon || tok == token::UnitCappedRam
                || tok == token::UnitHeavyScorpion || tok ==
                token::UnitMangonel || tok == token::UnitOnager || tok ==
                token::UnitScorpion || tok == token::UnitSiegeOnager || tok ==
                token::UnitSiegeRam || tok == token::UnitCamel || tok ==
                token::UnitCavalier || tok == token::UnitHeavyCamel || tok ==
                token::UnitHussar || tok == token::UnitKnight || tok ==
                token::UnitLightCavalry || tok == token::UnitPaladin || tok ==
                token::UnitScoutCavalry || tok == token::UnitVillager || tok ==
                token::UnitArcherLine || tok == token::UnitCavalryArcherLine ||
                tok == token::UnitSkirmisherLine || tok ==
                token::UnitEagleWarriorLine || tok == token::UnitMilitiamanLine
                || tok == token::UnitSpearmanLine || tok ==
                token::UnitBerserkLine || tok == token::UnitCataphractLine ||
                tok == token::UnitChuKoNuLine || tok ==
                token::UnitConquistadorLine || tok == token::UnitHuskarlLine ||
                tok == token::UnitJaguarWarriorLine || tok ==
                token::UnitJanissaryLine || tok == token::UnitLongbowmanLine ||
                tok == token::UnitMamelukeLine || tok ==
                token::UnitMangudaiLine || tok == token::UnitPlumedArcherLine
                || tok == token::UnitSamuraiLine || tok ==
                token::UnitTarkanLine || tok == token::UnitTeutonicKnightLine
                || tok == token::UnitThrowingAxemanLine || tok ==
                token::UnitWarElephantLine || tok == token::UnitWarWagonLine ||
                tok == token::UnitWoadRaiderLine || tok ==
                token::UnitCannonGalleonLine || tok ==
                token::UnitDemolitionShipLine || tok == token::UnitFireShipLine
                || tok == token::UnitGalleyLine || tok ==
                token::UnitLongboatLine || tok == token::UnitTurtleShipLine ||
                tok == token::UnitBatteringRamLine || tok ==
                token::UnitMangonelLine || tok == token::UnitScorpionLine ||
                tok == token::UnitCamelLine || tok == token::UnitKnightLine ||
                tok == token::UnitScoutCavalryLine || tok ==
                token::UnitMyEliteUniqueUnit || tok == token::UnitMyUniqueUnit
                || tok == token::UnitMyUniqueUnitLine || tok ==
                token::VictoryConditionNameStandard || tok ==
                token::VictoryConditionNameConquest || tok ==
                token::VictoryConditionNameTimeLimit || tok ==
                token::VictoryConditionNameScore || tok ==
                token::VictoryConditionNameCustom || tok ==
                token::WallTypeFortifiedWall || tok ==
                token::WallTypePalisadeWall || tok == token::WallTypeStoneWall
                || tok == token::WallTypeStoneWallLine);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YY_ASSERT (tok == token::ScriptEnd || tok == token::OpenParen || tok ==
                token::CloseParen || tok == token::RuleStart || tok ==
                token::ConditionActionSeparator || tok == token::Not || tok ==
                token::Or || tok == token::LoadIfDefined || tok == token::Else
                || tok == token::EndIf || tok == token::Space || tok ==
                token::NewLine || tok == token::AgeDarkAge || tok ==
                token::AgeFeudalAge || tok == token::AgeCastleAge || tok ==
                token::AgeImperialAge || tok == token::AgePostImperialAge ||
                tok == token::BuildingArcheryRange || tok ==
                token::BuildingBarracks || tok == token::BuildingBlacksmith ||
                tok == token::BuildingBombardTower || tok ==
                token::BuildingCastle || tok == token::BuildingDock || tok ==
                token::BuildingFarm || tok == token::BuildingFishTrap || tok ==
                token::BuildingGuardTower || tok == token::BuildingHouse || tok
                == token::BuildingKeep || tok == token::BuildingLumberCamp ||
                tok == token::BuildingMarket || tok == token::BuildingMill ||
                tok == token::BuildingMiningCamp || tok ==
                token::BuildingMonastery || tok == token::BuildingOutpost ||
                tok == token::BuildingSiegeWorkshop || tok ==
                token::BuildingStable || tok == token::BuildingTownCenter ||
                tok == token::BuildingUniversity || tok ==
                token::BuildingWatchTower || tok == token::BuildingWonder ||
                tok == token::BuildingWatchTowerLine || tok == token::CivBriton
                || tok == token::CivByzantine || tok == token::CivCeltic || tok
                == token::CivChinese || tok == token::CivFrankish || tok ==
                token::CivGothic || tok == token::CivJapanese || tok ==
                token::CivMongol || tok == token::CivPersian || tok ==
                token::CivSaracen || tok == token::CivTeutonic || tok ==
                token::CivTurkish || tok == token::CivViking || tok ==
                token::CivMyCiv || tok == token::CommodityFood || tok ==
                token::CommodityStone || tok == token::CommodityWood || tok ==
                token::CommodityGold || tok == token::DifficultyLevelEasiest ||
                tok == token::DifficultyLevelEasy || tok ==
                token::DifficultyLevelModerate || tok ==
                token::DifficultyLevelHard || tok ==
                token::DifficultyLevelHardest || tok ==
                token::DifficultyParameterAbilityToDodgeMissiles || tok ==
                token::DifficultyParameterAbilityToMaintainDistance || tok ==
                token::DiplomaticStanceAlly || tok ==
                token::DiplomaticStanceNeutral || tok ==
                token::DiplomaticStanceEnemy || tok == token::MapSizeTypeTiny
                || tok == token::MapSizeTypeSmall || tok ==
                token::MapSizeTypeMedium || tok == token::MapSizeTypeNormal ||
                tok == token::MapSizeTypeLarge || tok ==
                token::MapSizeTypeGiant || tok == token::MapTypeNameArabia ||
                tok == token::MapTypeNameArchipelago || tok ==
                token::MapTypeNameBaltic || tok ==
                token::MapTypeNameBlackForest || tok ==
                token::MapTypeNameCoastal || tok ==
                token::MapTypeNameContinental || tok ==
                token::MapTypeNameCraterLake || tok ==
                token::MapTypeNameFortress || tok == token::MapTypeNameGoldRush
                || tok == token::MapTypeNameHighland || tok ==
                token::MapTypeNameIslands || tok ==
                token::MapTypeNameMediterranean || tok ==
                token::MapTypeNameMigration || tok == token::MapTypeNameRivers
                || tok == token::MapTypeNameTeamIslands || tok ==
                token::MapTypeNameScenarioMap || tok ==
                token::PlayerNumberTypeAnyAlly || tok ==
                token::PlayerNumberTypeAnyComputer || tok ==
                token::PlayerNumberTypeAnyComputerAlly || tok ==
                token::PlayerNumberTypeAnyComputerEnemy || tok ==
                token::PlayerNumberTypeAnyComputerNeutral || tok ==
                token::PlayerNumberTypeAnyEnemy || tok ==
                token::PlayerNumberTypeAnyHuman || tok ==
                token::PlayerNumberTypeAnyHumanAlly || tok ==
                token::PlayerNumberTypeAnyHumanEnemy || tok ==
                token::PlayerNumberTypeAnyHumanNeutral || tok ==
                token::PlayerNumberTypeAnyNeutral || tok ==
                token::PlayerNumberTypeEveryAlly || tok ==
                token::PlayerNumberTypeEveryComputer || tok ==
                token::PlayerNumberTypeEveryEnemy || tok ==
                token::PlayerNumberTypeEveryHuman || tok ==
                token::PlayerNumberTypeEveryNeutral || tok ==
                token::PlayerNumberTypeMyPlayerNumber || tok ==
                token::RelOpLessThan || tok == token::RelOpLessOrEqual || tok
                == token::RelOpGreaterThan || tok == token::RelOpGreaterOrEqual
                || tok == token::RelOpEqual || tok == token::RelOpNotEqual ||
                tok == token::ResearchItemRiArbalest || tok ==
                token::ResearchItemRiCrossbow || tok ==
                token::ResearchItemRiEliteSkirmisher || tok ==
                token::ResearchItemRiHandCannon || tok ==
                token::ResearchItemRiHeavyCavalryArcher || tok ==
                token::ResearchItemRiChampion || tok ==
                token::ResearchItemRiEliteEagleWarrior || tok ==
                token::ResearchItemRiHalberdier || tok ==
                token::ResearchItemRiLongSwordsman || tok ==
                token::ResearchItemRiManAtArms || tok ==
                token::ResearchItemRiParthianTactics || tok ==
                token::ResearchItemRiPikeman || tok ==
                token::ResearchItemRiSquires || tok ==
                token::ResearchItemRiThumbRing || tok ==
                token::ResearchItemRiTracking || tok ==
                token::ResearchItemRiTwoHandedSwordsman || tok ==
                token::ResearchItemRiBlastFurnace || tok ==
                token::ResearchItemRiBodkinArrow || tok ==
                token::ResearchItemRiBracer || tok ==
                token::ResearchItemRiChainBarding || tok ==
                token::ResearchItemRiChainMail || tok ==
                token::ResearchItemRiFletching || tok ==
                token::ResearchItemRiForging || tok ==
                token::ResearchItemRiIronCasting || tok ==
                token::ResearchItemRiLeatherArcherArmor || tok ==
                token::ResearchItemRiPaddedArcherArmor || tok ==
                token::ResearchItemRiPlateBarding || tok ==
                token::ResearchItemRiPlateMail || tok ==
                token::ResearchItemRiRingArcherArmor || tok ==
                token::ResearchItemRiScaleBarding || tok ==
                token::ResearchItemRiScaleMail || tok ==
                token::ResearchItemRiConscription || tok ==
                token::ResearchItemRiHoardings || tok ==
                token::ResearchItemRiSappers || tok ==
                token::ResearchItemRiEliteBerserk || tok ==
                token::ResearchItemRiEliteCataphract || tok ==
                token::ResearchItemRiEliteChuKoNu || tok ==
                token::ResearchItemRiEliteHuskarl || tok ==
                token::ResearchItemRiEliteJanissary || tok ==
                token::ResearchItemRiEliteLongbowman || tok ==
                token::ResearchItemRiEliteMameluke || tok ==
                token::ResearchItemRiEliteMangudai || tok ==
                token::ResearchItemRiEliteSamurai || tok ==
                token::ResearchItemRiEliteTeutonicKnight || tok ==
                token::ResearchItemRiEliteThrowingAxeman || tok ==
                token::ResearchItemRiEliteWarElephant || tok ==
                token::ResearchItemRiEliteWoadRaider || tok ==
                token::ResearchItemRiMyUniqueEliteUnit || tok ==
                token::ResearchItemRiMyUniqueResearch || tok ==
                token::ResearchItemRiCannonGalleon || tok ==
                token::ResearchItemRiCareening || tok ==
                token::ResearchItemRiDeckGuns || tok ==
                token::ResearchItemRiDryDock || tok ==
                token::ResearchItemRiEliteLongboat || tok ==
                token::ResearchItemRiFastFireShip || tok ==
                token::ResearchItemRiGalleon || tok ==
                token::ResearchItemRiHeavyDemolitionShip || tok ==
                token::ResearchItemRiShipwright || tok ==
                token::ResearchItemRiWarGalley || tok ==
                token::ResearchItemRiBowSaw || tok ==
                token::ResearchItemRiDoubleBitAxe || tok ==
                token::ResearchItemRiTwoManSaw || tok ==
                token::ResearchItemRiBanking || tok ==
                token::ResearchItemRiCaravan || tok ==
                token::ResearchItemRiCartography || tok ==
                token::ResearchItemRiCoinage || tok ==
                token::ResearchItemRiGuilds || tok ==
                token::ResearchItemRiCropRotation || tok ==
                token::ResearchItemRiHeavyPlow || tok ==
                token::ResearchItemRiHorseCollar || tok ==
                token::ResearchItemRiGoldMining || tok ==
                token::ResearchItemRiGoldShaftMining || tok ==
                token::ResearchItemRiStoneMining || tok ==
                token::ResearchItemRiStoneShaftMining || tok ==
                token::ResearchItemRiAtonement || tok ==
                token::ResearchItemRiBlockPrinting || tok ==
                token::ResearchItemRiFaith || tok ==
                token::ResearchItemRiFervor || tok ==
                token::ResearchItemRiHerbalMedicine || tok ==
                token::ResearchItemRiHeresy || tok ==
                token::ResearchItemRiIllumination || tok ==
                token::ResearchItemRiRedemption || tok ==
                token::ResearchItemRiSanctity || tok ==
                token::ResearchItemRiTheocracy || tok ==
                token::ResearchItemRiBombardCannon || tok ==
                token::ResearchItemRiCappedRam || tok ==
                token::ResearchItemRiHeavyScorpion || tok ==
                token::ResearchItemRiOnager || tok ==
                token::ResearchItemRiScorpion || tok ==
                token::ResearchItemRiSiegeOnager || tok ==
                token::ResearchItemRiSiegeRam || tok ==
                token::ResearchItemRiBloodlines || tok ==
                token::ResearchItemRiCavalier || tok ==
                token::ResearchItemRiHeavyCamel || tok ==
                token::ResearchItemRiHusbandry || tok ==
                token::ResearchItemRiHussar || tok ==
                token::ResearchItemRiLightCavalry || tok ==
                token::ResearchItemRiPaladin || tok ==
                token::ResearchItemRiHandCart || tok ==
                token::ResearchItemRiLoom || tok ==
                token::ResearchItemRiTownPatrol || tok ==
                token::ResearchItemRiTownWatch || tok ==
                token::ResearchItemRiWheelBarrow || tok ==
                token::ResearchItemRiArchitecture || tok ==
                token::ResearchItemRiBallistics || tok ==
                token::ResearchItemRiBombardTower || tok ==
                token::ResearchItemRiChemistry || tok ==
                token::ResearchItemRiFortifiedWall || tok ==
                token::ResearchItemRiGuardTower || tok ==
                token::ResearchItemRiHeatedShot || tok ==
                token::ResearchItemRiKeep || tok ==
                token::ResearchItemRiMasonry || tok ==
                token::ResearchItemRiMurderHoles || tok ==
                token::ResearchItemRiSiegeEngineers || tok ==
                token::ResearchItemRiStonecutting || tok ==
                token::ResearchItemMyUniqueUnitUpgrade || tok ==
                token::ResearchItemMyUniqueResearch || tok ==
                token::StartingResourcesTypeLowResources || tok ==
                token::StartingResourcesTypeMediumResources || tok ==
                token::StartingResourcesTypeHighResources || tok ==
                token::StrategicNumberNameSnPercentCivilianExplorers || tok ==
                token::StrategicNumberNameSnPercentCivilianBuilders || tok ==
                token::StrategicNumberNameSnPercentCivilianGatherers || tok ==
                token::StrategicNumberNameSnCapCivilianExplorers || tok ==
                token::StrategicNumberNameSnCapCivilianBuilders || tok ==
                token::StrategicNumberNameSnCapCivilianGatherers || tok ==
                token::StrategicNumberNameSnMinimumAttackGroupSize || tok ==
                token::StrategicNumberNameSnTotalNumberExplorers || tok ==
                token::StrategicNumberNameSnPercentEnemySightedResponse || tok
                == token::StrategicNumberNameSnEnemySightedResponseDistance ||
                tok == token::StrategicNumberNameSnSentryDistance || tok ==
                token::StrategicNumberNameSnRelicReturnDistance || tok ==
                token::StrategicNumberNameSnMinimumDefendGroupSize || tok ==
                token::StrategicNumberNameSnMaximumAttackGroupSize || tok ==
                token::StrategicNumberNameSnMaximumDefendGroupSize || tok ==
                token::StrategicNumberNameSnMinimumPeaceLikeLevel || tok ==
                token::StrategicNumberNameSnPercentExplorationRequired || tok
                == token::StrategicNumberNameSnZeroPriorityDistance || tok ==
                token::StrategicNumberNameSnMinimumCivilianExplorers || tok ==
                token::StrategicNumberNameSnNumberAttackGroups || tok ==
                token::StrategicNumberNameSnNumberDefendGroups || tok ==
                token::StrategicNumberNameSnAttackGroupGatherSpacing || tok ==
                token::StrategicNumberNameSnNumberExploreGroups || tok ==
                token::StrategicNumberNameSnMinimumExploreGroupSize || tok ==
                token::StrategicNumberNameSnMaximumExploreGroupSize || tok ==
                token::StrategicNumberNameSnGoldDefendPriority || tok ==
                token::StrategicNumberNameSnStoneDefendPriority || tok ==
                token::StrategicNumberNameSnForageDefendPriority || tok ==
                token::StrategicNumberNameSnRelicDefendPriority || tok ==
                token::StrategicNumberNameSnTownDefendPriority || tok ==
                token::StrategicNumberNameSnDefenseDistance || tok ==
                token::StrategicNumberNameSnNumberBoatAttackGroups || tok ==
                token::StrategicNumberNameSnMinimumBoatAttackGroupSize || tok
                == token::StrategicNumberNameSnMaximumBoatAttackGroupSize ||
                tok == token::StrategicNumberNameSnNumberBoatExploreGroups ||
                tok == token::StrategicNumberNameSnMinimumBoatExploreGroupSize
                || tok ==
                token::StrategicNumberNameSnMaximumBoatExploreGroupSize || tok
                == token::StrategicNumberNameSnNumberBoatDefendGroups || tok ==
                token::StrategicNumberNameSnMinimumBoatDefendGroupSize || tok
                == token::StrategicNumberNameSnMaximumBoatDefendGroupSize ||
                tok == token::StrategicNumberNameSnDockDefendPriority || tok ==
                token::StrategicNumberNameSnSentryDistanceVariation || tok ==
                token::StrategicNumberNameSnMinimumTownSize || tok ==
                token::StrategicNumberNameSnMaximumTownSize || tok ==
                token::StrategicNumberNameSnGroupCommanderSelectionMethod ||
                tok == token::StrategicNumberNameSnConsecutiveIdleUnitLimit ||
                tok == token::StrategicNumberNameSnTargetEvaluationDistance ||
                tok == token::StrategicNumberNameSnTargetEvaluationHitpoints ||
                tok ==
                token::StrategicNumberNameSnTargetEvaluationDamageCapability ||
                tok == token::StrategicNumberNameSnTargetEvaluationKills || tok
                == token::StrategicNumberNameSnTargetEvaluationAllyProximity ||
                tok == token::StrategicNumberNameSnTargetEvaluationRof || tok
                == token::StrategicNumberNameSnTargetEvaluationRandomness ||
                tok == token::StrategicNumberNameSnCampMaxDistance || tok ==
                token::StrategicNumberNameSnMillMaxDistance || tok ==
                token::StrategicNumberNameSnTargetEvaluationAttackAttempts ||
                tok == token::StrategicNumberNameSnTargetEvaluationRange || tok
                == token::StrategicNumberNameSnDefendOverlapDistance || tok ==
                token::StrategicNumberNameSnScaleMinimumAttackGroupSize || tok
                == token::StrategicNumberNameSnScaleMaximumAttackGroupSize ||
                tok == token::StrategicNumberNameSnAttackGroupSizeRandomness ||
                tok == token::StrategicNumberNameSnScalingFrequency || tok ==
                token::StrategicNumberNameSnMaximumGaiaAttackResponse || tok ==
                token::StrategicNumberNameSnBuildFrequency || tok ==
                token::StrategicNumberNameSnAttackSeparationTimeRandomness ||
                tok == token::StrategicNumberNameSnAttackIntelligence || tok ==
                token::StrategicNumberNameSnInitialAttackDelay || tok ==
                token::StrategicNumberNameSnSaveScenarioInformation || tok ==
                token::StrategicNumberNameSnSpecialAttackType1 || tok ==
                token::StrategicNumberNameSnSpecialAttackInfluence1 || tok ==
                token::StrategicNumberNameSnMinimumWaterBodySizeForDock || tok
                == token::StrategicNumberNameSnNumberBuildAttemptsBeforeSkip ||
                tok == token::StrategicNumberNameSnMaxSkipsPerAttempt || tok ==
                token::StrategicNumberNameSnFoodGathererPercentage || tok ==
                token::StrategicNumberNameSnGoldGathererPercentage || tok ==
                token::StrategicNumberNameSnStoneGathererPercentage || tok ==
                token::StrategicNumberNameSnWoodGathererPercentage || tok ==
                token::StrategicNumberNameSnTargetEvaluationContinent || tok ==
                token::StrategicNumberNameSnTargetEvaluationSiegeWeapon || tok
                == token::StrategicNumberNameSnGroupLeaderDefenseDistance ||
                tok == token::StrategicNumberNameSnInitialAttackDelayType ||
                tok == token::StrategicNumberNameSnBlotExplorationMap || tok ==
                token::StrategicNumberNameSnBlotSize || tok ==
                token::StrategicNumberNameSnIntelligentGathering || tok ==
                token::StrategicNumberNameSnTaskUngroupedSoldiers || tok ==
                token::StrategicNumberNameSnTargetEvaluationBoat || tok ==
                token::StrategicNumberNameSnNumberEnemyObjectsRequired || tok
                == token::StrategicNumberNameSnNumberMaxSkipCycles || tok ==
                token::StrategicNumberNameSnRetaskGatherAmount || tok ==
                token::StrategicNumberNameSnMaxRetaskGatherAmount || tok ==
                token::StrategicNumberNameSnMaxBuildPlanGathererPercentage ||
                tok == token::StrategicNumberNameSnFoodDropsiteDistance || tok
                == token::StrategicNumberNameSnWoodDropsiteDistance || tok ==
                token::StrategicNumberNameSnStoneDropsiteDistance || tok ==
                token::StrategicNumberNameSnGoldDropsiteDistance || tok ==
                token::StrategicNumberNameSnInitialExplorationRequired || tok
                == token::StrategicNumberNameSnRandomPlacementFactor || tok ==
                token::StrategicNumberNameSnRequiredForestTiles || tok ==
                token::StrategicNumberNameSnAttackDiplomacyImpact || tok ==
                token::StrategicNumberNameSnPercentHalfExploration || tok ==
                token::StrategicNumberNameSnTargetEvaluationTimeKillRatio ||
                tok == token::StrategicNumberNameSnTargetEvaluationInProgress
                || tok == token::StrategicNumberNameSnAttackWinningPlayer ||
                tok == token::StrategicNumberNameSnCoopShareInformation || tok
                == token::StrategicNumberNameSnAttackWinningPlayerFactor || tok
                == token::StrategicNumberNameSnCoopShareAttacking || tok ==
                token::StrategicNumberNameSnCoopShareAttackingInterval || tok
                == token::StrategicNumberNameSnPercentageExploreExterminators
                || tok == token::StrategicNumberNameSnTrackPlayerHistory || tok
                == token::StrategicNumberNameSnMinimumDropsiteBuffer || tok ==
                token::StrategicNumberNameSnUseByTypeMaxGathering || tok ==
                token::StrategicNumberNameSnMinimumBoarHuntGroupSize || tok ==
                token::StrategicNumberNameSnMinimumAmountForTrading || tok ==
                token::StrategicNumberNameSnEasiestReactionPercentage || tok ==
                token::StrategicNumberNameSnEasierReactionPercentage || tok ==
                token::StrategicNumberNameSnHitsBeforeAllianceChange || tok ==
                token::StrategicNumberNameSnAllowCivilianDefense || tok ==
                token::StrategicNumberNameSnNumberForwardBuilders || tok ==
                token::StrategicNumberNameSnPercentAttackSoldiers || tok ==
                token::StrategicNumberNameSnPercentAttackBoats || tok ==
                token::StrategicNumberNameSnDoNotScaleForDifficultyLevel || tok
                == token::StrategicNumberNameSnGroupFormDistance || tok ==
                token::StrategicNumberNameSnIgnoreAttackGroupUnderAttack || tok
                == token::StrategicNumberNameSnGatherDefenseUnits || tok ==
                token::StrategicNumberNameSnMaximumWoodDropDistance || tok ==
                token::StrategicNumberNameSnMaximumFoodDropDistance || tok ==
                token::StrategicNumberNameSnMaximumHuntDropDistance || tok ==
                token::StrategicNumberNameSnMaximumFishBoatDropDistance || tok
                == token::StrategicNumberNameSnMaximumGoldDropDistance || tok
                == token::StrategicNumberNameSnMaximumStoneDropDistance || tok
                == token::StrategicNumberNameSnGatherIdleSoldiersAtCenter ||
                tok == token::StrategicNumberNameSnGarrisonRams || tok ==
                token::UnitArbalest || tok == token::UnitArcher || tok ==
                token::UnitCavalryArcher || tok == token::UnitCrossbowman ||
                tok == token::UnitEliteSkirmisher || tok ==
                token::UnitHandCannoneer || tok ==
                token::UnitHeavyCavalryArcher || tok == token::UnitSkirmisher
                || tok == token::UnitChampion || tok == token::UnitEagleWarrior
                || tok == token::UnitEliteEagleWarrior || tok ==
                token::UnitHalberdier || tok == token::UnitLongSwordsman || tok
                == token::UnitManAtArms || tok == token::UnitMilitiaman || tok
                == token::UnitPikeman || tok == token::UnitSpearman || tok ==
                token::UnitTwoHandedSwordsman || tok == token::UnitBerserk ||
                tok == token::UnitCataphract || tok == token::UnitChuKoNu ||
                tok == token::UnitConquistador || tok ==
                token::UnitEliteBerserk || tok == token::UnitEliteCataphract ||
                tok == token::UnitEliteChuKoNu || tok ==
                token::UnitEliteConquistador || tok == token::UnitEliteHuskarl
                || tok == token::UnitEliteJaguarWarrior || tok ==
                token::UnitEliteJanissary || tok == token::UnitEliteLongbowman
                || tok == token::UnitEliteMameluke || tok ==
                token::UnitEliteMangudai || tok == token::UnitElitePlumedArcher
                || tok == token::UnitEliteSamurai || tok ==
                token::UnitEliteTarkan || tok == token::UnitEliteTeutonicKnight
                || tok == token::UnitEliteThrowingAxeman || tok ==
                token::UnitEliteWarElephant || tok == token::UnitEliteWarWagon
                || tok == token::UnitEliteWoadRaider || tok ==
                token::UnitHuskarl || tok == token::UnitJaguarWarrior || tok ==
                token::UnitJanissary || tok == token::UnitLongbowman || tok ==
                token::UnitMameluke || tok == token::UnitMangudai || tok ==
                token::UnitPetard || tok == token::UnitPlumedArcher || tok ==
                token::UnitSamurai || tok == token::UnitTarkan || tok ==
                token::UnitTeutonicKnight || tok == token::UnitThrowingAxeman
                || tok == token::UnitTrebuchet || tok == token::UnitWarElephant
                || tok == token::UnitWarWagon || tok == token::UnitWoadRaider
                || tok == token::UnitCannonGalleon || tok ==
                token::UnitDemolitionShip || tok ==
                token::UnitEliteCannonGalleon || tok ==
                token::UnitEliteLongboat || tok == token::UnitEliteTurtleShip
                || tok == token::UnitFastFireShip || tok == token::UnitFireShip
                || tok == token::UnitFishingShip || tok == token::UnitGalleon
                || tok == token::UnitGalley || tok ==
                token::UnitHeavyDemolitionShip || tok == token::UnitLongboat ||
                tok == token::UnitTradeCog || tok == token::UnitTransportShip
                || tok == token::UnitTurtleShip || tok == token::UnitWarGalley
                || tok == token::UnitTradeCart || tok == token::UnitMissionary
                || tok == token::UnitMonk || tok == token::UnitBatteringRam ||
                tok == token::UnitBombardCannon || tok == token::UnitCappedRam
                || tok == token::UnitHeavyScorpion || tok ==
                token::UnitMangonel || tok == token::UnitOnager || tok ==
                token::UnitScorpion || tok == token::UnitSiegeOnager || tok ==
                token::UnitSiegeRam || tok == token::UnitCamel || tok ==
                token::UnitCavalier || tok == token::UnitHeavyCamel || tok ==
                token::UnitHussar || tok == token::UnitKnight || tok ==
                token::UnitLightCavalry || tok == token::UnitPaladin || tok ==
                token::UnitScoutCavalry || tok == token::UnitVillager || tok ==
                token::UnitArcherLine || tok == token::UnitCavalryArcherLine ||
                tok == token::UnitSkirmisherLine || tok ==
                token::UnitEagleWarriorLine || tok == token::UnitMilitiamanLine
                || tok == token::UnitSpearmanLine || tok ==
                token::UnitBerserkLine || tok == token::UnitCataphractLine ||
                tok == token::UnitChuKoNuLine || tok ==
                token::UnitConquistadorLine || tok == token::UnitHuskarlLine ||
                tok == token::UnitJaguarWarriorLine || tok ==
                token::UnitJanissaryLine || tok == token::UnitLongbowmanLine ||
                tok == token::UnitMamelukeLine || tok ==
                token::UnitMangudaiLine || tok == token::UnitPlumedArcherLine
                || tok == token::UnitSamuraiLine || tok ==
                token::UnitTarkanLine || tok == token::UnitTeutonicKnightLine
                || tok == token::UnitThrowingAxemanLine || tok ==
                token::UnitWarElephantLine || tok == token::UnitWarWagonLine ||
                tok == token::UnitWoadRaiderLine || tok ==
                token::UnitCannonGalleonLine || tok ==
                token::UnitDemolitionShipLine || tok == token::UnitFireShipLine
                || tok == token::UnitGalleyLine || tok ==
                token::UnitLongboatLine || tok == token::UnitTurtleShipLine ||
                tok == token::UnitBatteringRamLine || tok ==
                token::UnitMangonelLine || tok == token::UnitScorpionLine ||
                tok == token::UnitCamelLine || tok == token::UnitKnightLine ||
                tok == token::UnitScoutCavalryLine || tok ==
                token::UnitMyEliteUniqueUnit || tok == token::UnitMyUniqueUnit
                || tok == token::UnitMyUniqueUnitLine || tok ==
                token::VictoryConditionNameStandard || tok ==
                token::VictoryConditionNameConquest || tok ==
                token::VictoryConditionNameTimeLimit || tok ==
                token::VictoryConditionNameScore || tok ==
                token::VictoryConditionNameCustom || tok ==
                token::WallTypeFortifiedWall || tok ==
                token::WallTypePalisadeWall || tok == token::WallTypeStoneWall
                || tok == token::WallTypeStoneWallLine);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, ActionType v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::AcknowledgeEvent || tok ==
                token::AcknowledgeTaunt || tok == token::AttackNow || tok ==
                token::Build || tok == token::BuildForward || tok ==
                token::BuildGate || tok == token::BuildWall || tok ==
                token::BuyCommodity || tok == token::CcAddResource || tok ==
                token::ChatLocal || tok == token::ChatLocalToSelf || tok ==
                token::ChatLocalUsingId || tok == token::ChatLocalUsingRange ||
                tok == token::ChatToAll || tok == token::ChatToAllies || tok ==
                token::ChatToAlliesUsingId || tok ==
                token::ChatToAlliesUsingRange || tok == token::ChatToAllUsingId
                || tok == token::ChatToAllUsingRange || tok ==
                token::ChatToEnemies || tok == token::ChatToEnemiesUsingId ||
                tok == token::ChatToEnemiesUsingRange || tok ==
                token::ChatToPlayer || tok == token::ChatToPlayerUsingId || tok
                == token::ChatToPlayerUsingRange || tok == token::ChatTrace ||
                tok == token::ClearTributeMemory || tok ==
                token::DeleteBuilding || tok == token::DeleteUnit || tok ==
                token::DisableSelf || tok == token::DisableTimer || tok ==
                token::DoNothing || tok == token::EnableTimer || tok ==
                token::EnableWallPlacement || tok ==
                token::GenerateRandomNumber || tok == token::Log || tok ==
                token::LogTrace || tok == token::ReleaseEscrow || tok ==
                token::Research || tok == token::Resign || tok ==
                token::SellCommodity || tok == token::SetDifficultyParameter ||
                tok == token::SetDoctrine || tok == token::SetEscrowPercentage
                || tok == token::SetGoal || tok == token::SetSharedGoal || tok
                == token::SetSignal || tok == token::SetStance || tok ==
                token::SetStrategicNumber || tok == token::Spy || tok ==
                token::Taunt || tok == token::TauntUsingRange || tok ==
                token::Train || tok == token::TributeToPlayer);
      }
#else
      symbol_type (int tok, const ActionType& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::AcknowledgeEvent || tok ==
                token::AcknowledgeTaunt || tok == token::AttackNow || tok ==
                token::Build || tok == token::BuildForward || tok ==
                token::BuildGate || tok == token::BuildWall || tok ==
                token::BuyCommodity || tok == token::CcAddResource || tok ==
                token::ChatLocal || tok == token::ChatLocalToSelf || tok ==
                token::ChatLocalUsingId || tok == token::ChatLocalUsingRange ||
                tok == token::ChatToAll || tok == token::ChatToAllies || tok ==
                token::ChatToAlliesUsingId || tok ==
                token::ChatToAlliesUsingRange || tok == token::ChatToAllUsingId
                || tok == token::ChatToAllUsingRange || tok ==
                token::ChatToEnemies || tok == token::ChatToEnemiesUsingId ||
                tok == token::ChatToEnemiesUsingRange || tok ==
                token::ChatToPlayer || tok == token::ChatToPlayerUsingId || tok
                == token::ChatToPlayerUsingRange || tok == token::ChatTrace ||
                tok == token::ClearTributeMemory || tok ==
                token::DeleteBuilding || tok == token::DeleteUnit || tok ==
                token::DisableSelf || tok == token::DisableTimer || tok ==
                token::DoNothing || tok == token::EnableTimer || tok ==
                token::EnableWallPlacement || tok ==
                token::GenerateRandomNumber || tok == token::Log || tok ==
                token::LogTrace || tok == token::ReleaseEscrow || tok ==
                token::Research || tok == token::Resign || tok ==
                token::SellCommodity || tok == token::SetDifficultyParameter ||
                tok == token::SetDoctrine || tok == token::SetEscrowPercentage
                || tok == token::SetGoal || tok == token::SetSharedGoal || tok
                == token::SetSignal || tok == token::SetStance || tok ==
                token::SetStrategicNumber || tok == token::Spy || tok ==
                token::Taunt || tok == token::TauntUsingRange || tok ==
                token::Train || tok == token::TributeToPlayer);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Fact v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::AttackSoldierCount || tok ==
                token::AttackWarboatCount || tok == token::BuildingAvailable ||
                tok == token::BuildingCount || tok == token::BuildingCountTotal
                || tok == token::BuildingTypeCount || tok ==
                token::BuildingTypeCountTotal || tok ==
                token::CanAffordBuilding || tok == token::CanAffordCompleteWall
                || tok == token::CanAffordResearch || tok ==
                token::CanAffordUnit || tok == token::CanBuild || tok ==
                token::CanBuildGate || tok == token::CanBuildGateWithEscrow ||
                tok == token::CanBuildWall || tok ==
                token::CanBuildWallWithEscrow || tok ==
                token::CanBuildWithEscrow || tok == token::CanBuyCommodity ||
                tok == token::CanResearch || tok ==
                token::CanResearchWithEscrow || tok == token::CanSellCommodity
                || tok == token::CanSpy || tok == token::CanSpyWithEscrow ||
                tok == token::CanTrain || tok == token::CanTrainWithEscrow ||
                tok == token::CcPlayersBuildingCount || tok ==
                token::CcPlayersBuildingTypeCount || tok ==
                token::CcPlayersUnitCount || tok ==
                token::CcPlayersUnitTypeCount || tok == token::CheatsEnabled ||
                tok == token::CivilianPopulation || tok == token::CivSelected
                || tok == token::CommodityBuyingPrice || tok ==
                token::CommoditySellingPrice || tok == token::CurrentAge || tok
                == token::CurrentAgeTime || tok == token::CurrentScore || tok
                == token::DeathMatchGame || tok == token::DefendSoldierCount ||
                tok == token::DefendWarboatCount || tok == token::Difficulty ||
                tok == token::Doctrine || tok == token::DropsiteMinDistance ||
                tok == token::EnemyBuildingsInTown || tok ==
                token::EnemyCapturedRelics || tok == token::EscrowAmount || tok
                == token::EventDetected || tok == token::Falseval || tok ==
                token::FoodAmount || tok == token::GameTime || tok ==
                token::Goal || tok == token::GoldAmount || tok ==
                token::HousingHeadroom || tok == token::IdleFarmCount || tok ==
                token::MapSize || tok == token::MapType || tok ==
                token::MilitaryPopulation || tok == token::PlayerComputer ||
                tok == token::PlayerHuman || tok == token::PlayerInGame || tok
                == token::PlayerNumber || tok == token::PlayerResigned || tok
                == token::PlayersBuildingCount || tok ==
                token::PlayersBuildingTypeCount || tok == token::PlayersCiv ||
                tok == token::PlayersCivilianPopulation || tok ==
                token::PlayersCurrentAge || tok == token::PlayersCurrentAgeTime
                || tok == token::PlayersMilitaryPopulation || tok ==
                token::PlayersPopulation || tok == token::PlayersScore || tok
                == token::PlayersStance || tok == token::PlayersTribute || tok
                == token::PlayersTributeMemory || tok ==
                token::PlayersUnitCount || tok == token::PlayersUnitTypeCount
                || tok == token::PlayerValid || tok == token::Population || tok
                == token::PopulationCap || tok == token::PopulationHeadroom ||
                tok == token::RandomNumber || tok == token::RegicideGame || tok
                == token::ResearchAvailable || tok == token::ResearchCompleted
                || tok == token::ResourceFound || tok == token::SharedGoal ||
                tok == token::SheepAndForageTooFar || tok ==
                token::SoldierCount || tok == token::StanceToward || tok ==
                token::StartingAge || tok == token::StartingResources || tok ==
                token::StoneAmount || tok == token::StrategicNumber || tok ==
                token::TauntDetected || tok == token::TimerTriggered || tok ==
                token::TownUnderAttack || tok == token::Trueval || tok ==
                token::UnitAvailable || tok == token::UnitCount || tok ==
                token::UnitCountTotal || tok == token::UnitTypeCount || tok ==
                token::UnitTypeCountTotal || tok == token::VictoryCondition ||
                tok == token::WallCompletedPercentage || tok ==
                token::WallInvisiblePercentage || tok == token::WarboatCount ||
                tok == token::WoodAmount);
      }
#else
      symbol_type (int tok, const Fact& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::AttackSoldierCount || tok ==
                token::AttackWarboatCount || tok == token::BuildingAvailable ||
                tok == token::BuildingCount || tok == token::BuildingCountTotal
                || tok == token::BuildingTypeCount || tok ==
                token::BuildingTypeCountTotal || tok ==
                token::CanAffordBuilding || tok == token::CanAffordCompleteWall
                || tok == token::CanAffordResearch || tok ==
                token::CanAffordUnit || tok == token::CanBuild || tok ==
                token::CanBuildGate || tok == token::CanBuildGateWithEscrow ||
                tok == token::CanBuildWall || tok ==
                token::CanBuildWallWithEscrow || tok ==
                token::CanBuildWithEscrow || tok == token::CanBuyCommodity ||
                tok == token::CanResearch || tok ==
                token::CanResearchWithEscrow || tok == token::CanSellCommodity
                || tok == token::CanSpy || tok == token::CanSpyWithEscrow ||
                tok == token::CanTrain || tok == token::CanTrainWithEscrow ||
                tok == token::CcPlayersBuildingCount || tok ==
                token::CcPlayersBuildingTypeCount || tok ==
                token::CcPlayersUnitCount || tok ==
                token::CcPlayersUnitTypeCount || tok == token::CheatsEnabled ||
                tok == token::CivilianPopulation || tok == token::CivSelected
                || tok == token::CommodityBuyingPrice || tok ==
                token::CommoditySellingPrice || tok == token::CurrentAge || tok
                == token::CurrentAgeTime || tok == token::CurrentScore || tok
                == token::DeathMatchGame || tok == token::DefendSoldierCount ||
                tok == token::DefendWarboatCount || tok == token::Difficulty ||
                tok == token::Doctrine || tok == token::DropsiteMinDistance ||
                tok == token::EnemyBuildingsInTown || tok ==
                token::EnemyCapturedRelics || tok == token::EscrowAmount || tok
                == token::EventDetected || tok == token::Falseval || tok ==
                token::FoodAmount || tok == token::GameTime || tok ==
                token::Goal || tok == token::GoldAmount || tok ==
                token::HousingHeadroom || tok == token::IdleFarmCount || tok ==
                token::MapSize || tok == token::MapType || tok ==
                token::MilitaryPopulation || tok == token::PlayerComputer ||
                tok == token::PlayerHuman || tok == token::PlayerInGame || tok
                == token::PlayerNumber || tok == token::PlayerResigned || tok
                == token::PlayersBuildingCount || tok ==
                token::PlayersBuildingTypeCount || tok == token::PlayersCiv ||
                tok == token::PlayersCivilianPopulation || tok ==
                token::PlayersCurrentAge || tok == token::PlayersCurrentAgeTime
                || tok == token::PlayersMilitaryPopulation || tok ==
                token::PlayersPopulation || tok == token::PlayersScore || tok
                == token::PlayersStance || tok == token::PlayersTribute || tok
                == token::PlayersTributeMemory || tok ==
                token::PlayersUnitCount || tok == token::PlayersUnitTypeCount
                || tok == token::PlayerValid || tok == token::Population || tok
                == token::PopulationCap || tok == token::PopulationHeadroom ||
                tok == token::RandomNumber || tok == token::RegicideGame || tok
                == token::ResearchAvailable || tok == token::ResearchCompleted
                || tok == token::ResourceFound || tok == token::SharedGoal ||
                tok == token::SheepAndForageTooFar || tok ==
                token::SoldierCount || tok == token::StanceToward || tok ==
                token::StartingAge || tok == token::StartingResources || tok ==
                token::StoneAmount || tok == token::StrategicNumber || tok ==
                token::TauntDetected || tok == token::TimerTriggered || tok ==
                token::TownUnderAttack || tok == token::Trueval || tok ==
                token::UnitAvailable || tok == token::UnitCount || tok ==
                token::UnitCountTotal || tok == token::UnitTypeCount || tok ==
                token::UnitTypeCountTotal || tok == token::VictoryCondition ||
                tok == token::WallCompletedPercentage || tok ==
                token::WallInvisiblePercentage || tok == token::WarboatCount ||
                tok == token::WoodAmount);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::Number);
      }
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::Number);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::String || tok == token::SymbolName);
      }
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::String || tok == token::SymbolName);
      }
#endif
    };

    /// Build a parser object.
    ScriptParser (ai::ScriptLoader &driver_yyarg, ai::ScriptTokenizer &scanner_yyarg);
    virtual ~ScriptParser ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ScriptEnd (location_type l)
      {
        return symbol_type (token::ScriptEnd, std::move (l));
      }
#else
      static
      symbol_type
      make_ScriptEnd (const location_type& l)
      {
        return symbol_type (token::ScriptEnd, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Number (int v, location_type l)
      {
        return symbol_type (token::Number, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Number (const int& v, const location_type& l)
      {
        return symbol_type (token::Number, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_String (std::string v, location_type l)
      {
        return symbol_type (token::String, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_String (const std::string& v, const location_type& l)
      {
        return symbol_type (token::String, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SymbolName (std::string v, location_type l)
      {
        return symbol_type (token::SymbolName, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SymbolName (const std::string& v, const location_type& l)
      {
        return symbol_type (token::SymbolName, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OpenParen (location_type l)
      {
        return symbol_type (token::OpenParen, std::move (l));
      }
#else
      static
      symbol_type
      make_OpenParen (const location_type& l)
      {
        return symbol_type (token::OpenParen, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CloseParen (location_type l)
      {
        return symbol_type (token::CloseParen, std::move (l));
      }
#else
      static
      symbol_type
      make_CloseParen (const location_type& l)
      {
        return symbol_type (token::CloseParen, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RuleStart (location_type l)
      {
        return symbol_type (token::RuleStart, std::move (l));
      }
#else
      static
      symbol_type
      make_RuleStart (const location_type& l)
      {
        return symbol_type (token::RuleStart, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ConditionActionSeparator (location_type l)
      {
        return symbol_type (token::ConditionActionSeparator, std::move (l));
      }
#else
      static
      symbol_type
      make_ConditionActionSeparator (const location_type& l)
      {
        return symbol_type (token::ConditionActionSeparator, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Not (location_type l)
      {
        return symbol_type (token::Not, std::move (l));
      }
#else
      static
      symbol_type
      make_Not (const location_type& l)
      {
        return symbol_type (token::Not, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Or (location_type l)
      {
        return symbol_type (token::Or, std::move (l));
      }
#else
      static
      symbol_type
      make_Or (const location_type& l)
      {
        return symbol_type (token::Or, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LoadIfDefined (location_type l)
      {
        return symbol_type (token::LoadIfDefined, std::move (l));
      }
#else
      static
      symbol_type
      make_LoadIfDefined (const location_type& l)
      {
        return symbol_type (token::LoadIfDefined, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Else (location_type l)
      {
        return symbol_type (token::Else, std::move (l));
      }
#else
      static
      symbol_type
      make_Else (const location_type& l)
      {
        return symbol_type (token::Else, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EndIf (location_type l)
      {
        return symbol_type (token::EndIf, std::move (l));
      }
#else
      static
      symbol_type
      make_EndIf (const location_type& l)
      {
        return symbol_type (token::EndIf, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Space (location_type l)
      {
        return symbol_type (token::Space, std::move (l));
      }
#else
      static
      symbol_type
      make_Space (const location_type& l)
      {
        return symbol_type (token::Space, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NewLine (location_type l)
      {
        return symbol_type (token::NewLine, std::move (l));
      }
#else
      static
      symbol_type
      make_NewLine (const location_type& l)
      {
        return symbol_type (token::NewLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AcknowledgeEvent (ActionType v, location_type l)
      {
        return symbol_type (token::AcknowledgeEvent, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AcknowledgeEvent (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::AcknowledgeEvent, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AcknowledgeTaunt (ActionType v, location_type l)
      {
        return symbol_type (token::AcknowledgeTaunt, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AcknowledgeTaunt (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::AcknowledgeTaunt, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AgeDarkAge (location_type l)
      {
        return symbol_type (token::AgeDarkAge, std::move (l));
      }
#else
      static
      symbol_type
      make_AgeDarkAge (const location_type& l)
      {
        return symbol_type (token::AgeDarkAge, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AgeFeudalAge (location_type l)
      {
        return symbol_type (token::AgeFeudalAge, std::move (l));
      }
#else
      static
      symbol_type
      make_AgeFeudalAge (const location_type& l)
      {
        return symbol_type (token::AgeFeudalAge, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AgeCastleAge (location_type l)
      {
        return symbol_type (token::AgeCastleAge, std::move (l));
      }
#else
      static
      symbol_type
      make_AgeCastleAge (const location_type& l)
      {
        return symbol_type (token::AgeCastleAge, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AgeImperialAge (location_type l)
      {
        return symbol_type (token::AgeImperialAge, std::move (l));
      }
#else
      static
      symbol_type
      make_AgeImperialAge (const location_type& l)
      {
        return symbol_type (token::AgeImperialAge, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AgePostImperialAge (location_type l)
      {
        return symbol_type (token::AgePostImperialAge, std::move (l));
      }
#else
      static
      symbol_type
      make_AgePostImperialAge (const location_type& l)
      {
        return symbol_type (token::AgePostImperialAge, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AttackNow (ActionType v, location_type l)
      {
        return symbol_type (token::AttackNow, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AttackNow (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::AttackNow, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AttackSoldierCount (Fact v, location_type l)
      {
        return symbol_type (token::AttackSoldierCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AttackSoldierCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::AttackSoldierCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AttackWarboatCount (Fact v, location_type l)
      {
        return symbol_type (token::AttackWarboatCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AttackWarboatCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::AttackWarboatCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Build (ActionType v, location_type l)
      {
        return symbol_type (token::Build, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Build (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::Build, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildForward (ActionType v, location_type l)
      {
        return symbol_type (token::BuildForward, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BuildForward (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::BuildForward, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildGate (ActionType v, location_type l)
      {
        return symbol_type (token::BuildGate, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BuildGate (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::BuildGate, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingArcheryRange (location_type l)
      {
        return symbol_type (token::BuildingArcheryRange, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingArcheryRange (const location_type& l)
      {
        return symbol_type (token::BuildingArcheryRange, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingBarracks (location_type l)
      {
        return symbol_type (token::BuildingBarracks, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingBarracks (const location_type& l)
      {
        return symbol_type (token::BuildingBarracks, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingBlacksmith (location_type l)
      {
        return symbol_type (token::BuildingBlacksmith, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingBlacksmith (const location_type& l)
      {
        return symbol_type (token::BuildingBlacksmith, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingBombardTower (location_type l)
      {
        return symbol_type (token::BuildingBombardTower, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingBombardTower (const location_type& l)
      {
        return symbol_type (token::BuildingBombardTower, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingCastle (location_type l)
      {
        return symbol_type (token::BuildingCastle, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingCastle (const location_type& l)
      {
        return symbol_type (token::BuildingCastle, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingDock (location_type l)
      {
        return symbol_type (token::BuildingDock, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingDock (const location_type& l)
      {
        return symbol_type (token::BuildingDock, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingFarm (location_type l)
      {
        return symbol_type (token::BuildingFarm, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingFarm (const location_type& l)
      {
        return symbol_type (token::BuildingFarm, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingFishTrap (location_type l)
      {
        return symbol_type (token::BuildingFishTrap, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingFishTrap (const location_type& l)
      {
        return symbol_type (token::BuildingFishTrap, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingGuardTower (location_type l)
      {
        return symbol_type (token::BuildingGuardTower, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingGuardTower (const location_type& l)
      {
        return symbol_type (token::BuildingGuardTower, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingHouse (location_type l)
      {
        return symbol_type (token::BuildingHouse, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingHouse (const location_type& l)
      {
        return symbol_type (token::BuildingHouse, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingKeep (location_type l)
      {
        return symbol_type (token::BuildingKeep, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingKeep (const location_type& l)
      {
        return symbol_type (token::BuildingKeep, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingLumberCamp (location_type l)
      {
        return symbol_type (token::BuildingLumberCamp, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingLumberCamp (const location_type& l)
      {
        return symbol_type (token::BuildingLumberCamp, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingMarket (location_type l)
      {
        return symbol_type (token::BuildingMarket, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingMarket (const location_type& l)
      {
        return symbol_type (token::BuildingMarket, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingMill (location_type l)
      {
        return symbol_type (token::BuildingMill, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingMill (const location_type& l)
      {
        return symbol_type (token::BuildingMill, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingMiningCamp (location_type l)
      {
        return symbol_type (token::BuildingMiningCamp, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingMiningCamp (const location_type& l)
      {
        return symbol_type (token::BuildingMiningCamp, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingMonastery (location_type l)
      {
        return symbol_type (token::BuildingMonastery, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingMonastery (const location_type& l)
      {
        return symbol_type (token::BuildingMonastery, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingOutpost (location_type l)
      {
        return symbol_type (token::BuildingOutpost, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingOutpost (const location_type& l)
      {
        return symbol_type (token::BuildingOutpost, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingSiegeWorkshop (location_type l)
      {
        return symbol_type (token::BuildingSiegeWorkshop, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingSiegeWorkshop (const location_type& l)
      {
        return symbol_type (token::BuildingSiegeWorkshop, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingStable (location_type l)
      {
        return symbol_type (token::BuildingStable, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingStable (const location_type& l)
      {
        return symbol_type (token::BuildingStable, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingTownCenter (location_type l)
      {
        return symbol_type (token::BuildingTownCenter, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingTownCenter (const location_type& l)
      {
        return symbol_type (token::BuildingTownCenter, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingUniversity (location_type l)
      {
        return symbol_type (token::BuildingUniversity, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingUniversity (const location_type& l)
      {
        return symbol_type (token::BuildingUniversity, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingWatchTower (location_type l)
      {
        return symbol_type (token::BuildingWatchTower, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingWatchTower (const location_type& l)
      {
        return symbol_type (token::BuildingWatchTower, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingWonder (location_type l)
      {
        return symbol_type (token::BuildingWonder, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingWonder (const location_type& l)
      {
        return symbol_type (token::BuildingWonder, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingWatchTowerLine (location_type l)
      {
        return symbol_type (token::BuildingWatchTowerLine, std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingWatchTowerLine (const location_type& l)
      {
        return symbol_type (token::BuildingWatchTowerLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingAvailable (Fact v, location_type l)
      {
        return symbol_type (token::BuildingAvailable, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingAvailable (const Fact& v, const location_type& l)
      {
        return symbol_type (token::BuildingAvailable, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingCount (Fact v, location_type l)
      {
        return symbol_type (token::BuildingCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::BuildingCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingCountTotal (Fact v, location_type l)
      {
        return symbol_type (token::BuildingCountTotal, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingCountTotal (const Fact& v, const location_type& l)
      {
        return symbol_type (token::BuildingCountTotal, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingTypeCount (Fact v, location_type l)
      {
        return symbol_type (token::BuildingTypeCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingTypeCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::BuildingTypeCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildingTypeCountTotal (Fact v, location_type l)
      {
        return symbol_type (token::BuildingTypeCountTotal, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BuildingTypeCountTotal (const Fact& v, const location_type& l)
      {
        return symbol_type (token::BuildingTypeCountTotal, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuildWall (ActionType v, location_type l)
      {
        return symbol_type (token::BuildWall, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BuildWall (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::BuildWall, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BuyCommodity (ActionType v, location_type l)
      {
        return symbol_type (token::BuyCommodity, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BuyCommodity (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::BuyCommodity, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanAffordBuilding (Fact v, location_type l)
      {
        return symbol_type (token::CanAffordBuilding, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanAffordBuilding (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanAffordBuilding, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanAffordCompleteWall (Fact v, location_type l)
      {
        return symbol_type (token::CanAffordCompleteWall, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanAffordCompleteWall (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanAffordCompleteWall, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanAffordResearch (Fact v, location_type l)
      {
        return symbol_type (token::CanAffordResearch, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanAffordResearch (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanAffordResearch, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanAffordUnit (Fact v, location_type l)
      {
        return symbol_type (token::CanAffordUnit, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanAffordUnit (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanAffordUnit, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanBuild (Fact v, location_type l)
      {
        return symbol_type (token::CanBuild, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanBuild (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanBuild, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanBuildGate (Fact v, location_type l)
      {
        return symbol_type (token::CanBuildGate, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanBuildGate (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanBuildGate, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanBuildGateWithEscrow (Fact v, location_type l)
      {
        return symbol_type (token::CanBuildGateWithEscrow, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanBuildGateWithEscrow (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanBuildGateWithEscrow, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanBuildWall (Fact v, location_type l)
      {
        return symbol_type (token::CanBuildWall, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanBuildWall (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanBuildWall, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanBuildWallWithEscrow (Fact v, location_type l)
      {
        return symbol_type (token::CanBuildWallWithEscrow, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanBuildWallWithEscrow (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanBuildWallWithEscrow, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanBuildWithEscrow (Fact v, location_type l)
      {
        return symbol_type (token::CanBuildWithEscrow, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanBuildWithEscrow (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanBuildWithEscrow, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanBuyCommodity (Fact v, location_type l)
      {
        return symbol_type (token::CanBuyCommodity, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanBuyCommodity (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanBuyCommodity, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanResearch (Fact v, location_type l)
      {
        return symbol_type (token::CanResearch, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanResearch (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanResearch, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanResearchWithEscrow (Fact v, location_type l)
      {
        return symbol_type (token::CanResearchWithEscrow, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanResearchWithEscrow (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanResearchWithEscrow, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanSellCommodity (Fact v, location_type l)
      {
        return symbol_type (token::CanSellCommodity, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanSellCommodity (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanSellCommodity, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanSpy (Fact v, location_type l)
      {
        return symbol_type (token::CanSpy, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanSpy (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanSpy, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanSpyWithEscrow (Fact v, location_type l)
      {
        return symbol_type (token::CanSpyWithEscrow, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanSpyWithEscrow (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanSpyWithEscrow, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanTrain (Fact v, location_type l)
      {
        return symbol_type (token::CanTrain, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanTrain (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanTrain, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CanTrainWithEscrow (Fact v, location_type l)
      {
        return symbol_type (token::CanTrainWithEscrow, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CanTrainWithEscrow (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CanTrainWithEscrow, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CcAddResource (ActionType v, location_type l)
      {
        return symbol_type (token::CcAddResource, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CcAddResource (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::CcAddResource, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CcPlayersBuildingCount (Fact v, location_type l)
      {
        return symbol_type (token::CcPlayersBuildingCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CcPlayersBuildingCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CcPlayersBuildingCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CcPlayersBuildingTypeCount (Fact v, location_type l)
      {
        return symbol_type (token::CcPlayersBuildingTypeCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CcPlayersBuildingTypeCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CcPlayersBuildingTypeCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CcPlayersUnitCount (Fact v, location_type l)
      {
        return symbol_type (token::CcPlayersUnitCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CcPlayersUnitCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CcPlayersUnitCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CcPlayersUnitTypeCount (Fact v, location_type l)
      {
        return symbol_type (token::CcPlayersUnitTypeCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CcPlayersUnitTypeCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CcPlayersUnitTypeCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatLocal (ActionType v, location_type l)
      {
        return symbol_type (token::ChatLocal, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatLocal (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatLocal, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatLocalToSelf (ActionType v, location_type l)
      {
        return symbol_type (token::ChatLocalToSelf, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatLocalToSelf (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatLocalToSelf, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatLocalUsingId (ActionType v, location_type l)
      {
        return symbol_type (token::ChatLocalUsingId, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatLocalUsingId (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatLocalUsingId, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatLocalUsingRange (ActionType v, location_type l)
      {
        return symbol_type (token::ChatLocalUsingRange, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatLocalUsingRange (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatLocalUsingRange, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToAll (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToAll, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToAll (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToAll, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToAllies (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToAllies, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToAllies (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToAllies, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToAlliesUsingId (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToAlliesUsingId, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToAlliesUsingId (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToAlliesUsingId, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToAlliesUsingRange (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToAlliesUsingRange, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToAlliesUsingRange (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToAlliesUsingRange, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToAllUsingId (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToAllUsingId, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToAllUsingId (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToAllUsingId, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToAllUsingRange (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToAllUsingRange, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToAllUsingRange (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToAllUsingRange, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToEnemies (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToEnemies, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToEnemies (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToEnemies, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToEnemiesUsingId (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToEnemiesUsingId, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToEnemiesUsingId (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToEnemiesUsingId, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToEnemiesUsingRange (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToEnemiesUsingRange, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToEnemiesUsingRange (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToEnemiesUsingRange, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToPlayer (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToPlayer, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToPlayer (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToPlayer, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToPlayerUsingId (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToPlayerUsingId, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToPlayerUsingId (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToPlayerUsingId, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatToPlayerUsingRange (ActionType v, location_type l)
      {
        return symbol_type (token::ChatToPlayerUsingRange, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatToPlayerUsingRange (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatToPlayerUsingRange, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ChatTrace (ActionType v, location_type l)
      {
        return symbol_type (token::ChatTrace, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ChatTrace (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ChatTrace, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CheatsEnabled (Fact v, location_type l)
      {
        return symbol_type (token::CheatsEnabled, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CheatsEnabled (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CheatsEnabled, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivBriton (location_type l)
      {
        return symbol_type (token::CivBriton, std::move (l));
      }
#else
      static
      symbol_type
      make_CivBriton (const location_type& l)
      {
        return symbol_type (token::CivBriton, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivByzantine (location_type l)
      {
        return symbol_type (token::CivByzantine, std::move (l));
      }
#else
      static
      symbol_type
      make_CivByzantine (const location_type& l)
      {
        return symbol_type (token::CivByzantine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivCeltic (location_type l)
      {
        return symbol_type (token::CivCeltic, std::move (l));
      }
#else
      static
      symbol_type
      make_CivCeltic (const location_type& l)
      {
        return symbol_type (token::CivCeltic, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivChinese (location_type l)
      {
        return symbol_type (token::CivChinese, std::move (l));
      }
#else
      static
      symbol_type
      make_CivChinese (const location_type& l)
      {
        return symbol_type (token::CivChinese, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivFrankish (location_type l)
      {
        return symbol_type (token::CivFrankish, std::move (l));
      }
#else
      static
      symbol_type
      make_CivFrankish (const location_type& l)
      {
        return symbol_type (token::CivFrankish, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivGothic (location_type l)
      {
        return symbol_type (token::CivGothic, std::move (l));
      }
#else
      static
      symbol_type
      make_CivGothic (const location_type& l)
      {
        return symbol_type (token::CivGothic, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivJapanese (location_type l)
      {
        return symbol_type (token::CivJapanese, std::move (l));
      }
#else
      static
      symbol_type
      make_CivJapanese (const location_type& l)
      {
        return symbol_type (token::CivJapanese, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivMongol (location_type l)
      {
        return symbol_type (token::CivMongol, std::move (l));
      }
#else
      static
      symbol_type
      make_CivMongol (const location_type& l)
      {
        return symbol_type (token::CivMongol, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivPersian (location_type l)
      {
        return symbol_type (token::CivPersian, std::move (l));
      }
#else
      static
      symbol_type
      make_CivPersian (const location_type& l)
      {
        return symbol_type (token::CivPersian, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivSaracen (location_type l)
      {
        return symbol_type (token::CivSaracen, std::move (l));
      }
#else
      static
      symbol_type
      make_CivSaracen (const location_type& l)
      {
        return symbol_type (token::CivSaracen, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivTeutonic (location_type l)
      {
        return symbol_type (token::CivTeutonic, std::move (l));
      }
#else
      static
      symbol_type
      make_CivTeutonic (const location_type& l)
      {
        return symbol_type (token::CivTeutonic, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivTurkish (location_type l)
      {
        return symbol_type (token::CivTurkish, std::move (l));
      }
#else
      static
      symbol_type
      make_CivTurkish (const location_type& l)
      {
        return symbol_type (token::CivTurkish, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivViking (location_type l)
      {
        return symbol_type (token::CivViking, std::move (l));
      }
#else
      static
      symbol_type
      make_CivViking (const location_type& l)
      {
        return symbol_type (token::CivViking, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivMyCiv (location_type l)
      {
        return symbol_type (token::CivMyCiv, std::move (l));
      }
#else
      static
      symbol_type
      make_CivMyCiv (const location_type& l)
      {
        return symbol_type (token::CivMyCiv, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivilianPopulation (Fact v, location_type l)
      {
        return symbol_type (token::CivilianPopulation, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CivilianPopulation (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CivilianPopulation, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CivSelected (Fact v, location_type l)
      {
        return symbol_type (token::CivSelected, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CivSelected (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CivSelected, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ClearTributeMemory (ActionType v, location_type l)
      {
        return symbol_type (token::ClearTributeMemory, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ClearTributeMemory (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ClearTributeMemory, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CommodityBuyingPrice (Fact v, location_type l)
      {
        return symbol_type (token::CommodityBuyingPrice, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CommodityBuyingPrice (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CommodityBuyingPrice, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CommodityFood (location_type l)
      {
        return symbol_type (token::CommodityFood, std::move (l));
      }
#else
      static
      symbol_type
      make_CommodityFood (const location_type& l)
      {
        return symbol_type (token::CommodityFood, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CommodityStone (location_type l)
      {
        return symbol_type (token::CommodityStone, std::move (l));
      }
#else
      static
      symbol_type
      make_CommodityStone (const location_type& l)
      {
        return symbol_type (token::CommodityStone, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CommodityWood (location_type l)
      {
        return symbol_type (token::CommodityWood, std::move (l));
      }
#else
      static
      symbol_type
      make_CommodityWood (const location_type& l)
      {
        return symbol_type (token::CommodityWood, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CommodityGold (location_type l)
      {
        return symbol_type (token::CommodityGold, std::move (l));
      }
#else
      static
      symbol_type
      make_CommodityGold (const location_type& l)
      {
        return symbol_type (token::CommodityGold, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CommoditySellingPrice (Fact v, location_type l)
      {
        return symbol_type (token::CommoditySellingPrice, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CommoditySellingPrice (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CommoditySellingPrice, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CurrentAge (Fact v, location_type l)
      {
        return symbol_type (token::CurrentAge, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CurrentAge (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CurrentAge, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CurrentAgeTime (Fact v, location_type l)
      {
        return symbol_type (token::CurrentAgeTime, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CurrentAgeTime (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CurrentAgeTime, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CurrentScore (Fact v, location_type l)
      {
        return symbol_type (token::CurrentScore, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CurrentScore (const Fact& v, const location_type& l)
      {
        return symbol_type (token::CurrentScore, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DeathMatchGame (Fact v, location_type l)
      {
        return symbol_type (token::DeathMatchGame, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DeathMatchGame (const Fact& v, const location_type& l)
      {
        return symbol_type (token::DeathMatchGame, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DefendSoldierCount (Fact v, location_type l)
      {
        return symbol_type (token::DefendSoldierCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DefendSoldierCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::DefendSoldierCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DefendWarboatCount (Fact v, location_type l)
      {
        return symbol_type (token::DefendWarboatCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DefendWarboatCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::DefendWarboatCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DeleteBuilding (ActionType v, location_type l)
      {
        return symbol_type (token::DeleteBuilding, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DeleteBuilding (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::DeleteBuilding, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DeleteUnit (ActionType v, location_type l)
      {
        return symbol_type (token::DeleteUnit, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DeleteUnit (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::DeleteUnit, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Difficulty (Fact v, location_type l)
      {
        return symbol_type (token::Difficulty, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Difficulty (const Fact& v, const location_type& l)
      {
        return symbol_type (token::Difficulty, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DifficultyLevelEasiest (location_type l)
      {
        return symbol_type (token::DifficultyLevelEasiest, std::move (l));
      }
#else
      static
      symbol_type
      make_DifficultyLevelEasiest (const location_type& l)
      {
        return symbol_type (token::DifficultyLevelEasiest, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DifficultyLevelEasy (location_type l)
      {
        return symbol_type (token::DifficultyLevelEasy, std::move (l));
      }
#else
      static
      symbol_type
      make_DifficultyLevelEasy (const location_type& l)
      {
        return symbol_type (token::DifficultyLevelEasy, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DifficultyLevelModerate (location_type l)
      {
        return symbol_type (token::DifficultyLevelModerate, std::move (l));
      }
#else
      static
      symbol_type
      make_DifficultyLevelModerate (const location_type& l)
      {
        return symbol_type (token::DifficultyLevelModerate, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DifficultyLevelHard (location_type l)
      {
        return symbol_type (token::DifficultyLevelHard, std::move (l));
      }
#else
      static
      symbol_type
      make_DifficultyLevelHard (const location_type& l)
      {
        return symbol_type (token::DifficultyLevelHard, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DifficultyLevelHardest (location_type l)
      {
        return symbol_type (token::DifficultyLevelHardest, std::move (l));
      }
#else
      static
      symbol_type
      make_DifficultyLevelHardest (const location_type& l)
      {
        return symbol_type (token::DifficultyLevelHardest, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DifficultyParameterAbilityToDodgeMissiles (location_type l)
      {
        return symbol_type (token::DifficultyParameterAbilityToDodgeMissiles, std::move (l));
      }
#else
      static
      symbol_type
      make_DifficultyParameterAbilityToDodgeMissiles (const location_type& l)
      {
        return symbol_type (token::DifficultyParameterAbilityToDodgeMissiles, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DifficultyParameterAbilityToMaintainDistance (location_type l)
      {
        return symbol_type (token::DifficultyParameterAbilityToMaintainDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_DifficultyParameterAbilityToMaintainDistance (const location_type& l)
      {
        return symbol_type (token::DifficultyParameterAbilityToMaintainDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DiplomaticStanceAlly (location_type l)
      {
        return symbol_type (token::DiplomaticStanceAlly, std::move (l));
      }
#else
      static
      symbol_type
      make_DiplomaticStanceAlly (const location_type& l)
      {
        return symbol_type (token::DiplomaticStanceAlly, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DiplomaticStanceNeutral (location_type l)
      {
        return symbol_type (token::DiplomaticStanceNeutral, std::move (l));
      }
#else
      static
      symbol_type
      make_DiplomaticStanceNeutral (const location_type& l)
      {
        return symbol_type (token::DiplomaticStanceNeutral, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DiplomaticStanceEnemy (location_type l)
      {
        return symbol_type (token::DiplomaticStanceEnemy, std::move (l));
      }
#else
      static
      symbol_type
      make_DiplomaticStanceEnemy (const location_type& l)
      {
        return symbol_type (token::DiplomaticStanceEnemy, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DisableSelf (ActionType v, location_type l)
      {
        return symbol_type (token::DisableSelf, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DisableSelf (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::DisableSelf, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DisableTimer (ActionType v, location_type l)
      {
        return symbol_type (token::DisableTimer, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DisableTimer (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::DisableTimer, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Doctrine (Fact v, location_type l)
      {
        return symbol_type (token::Doctrine, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Doctrine (const Fact& v, const location_type& l)
      {
        return symbol_type (token::Doctrine, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DoNothing (ActionType v, location_type l)
      {
        return symbol_type (token::DoNothing, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DoNothing (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::DoNothing, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DropsiteMinDistance (Fact v, location_type l)
      {
        return symbol_type (token::DropsiteMinDistance, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DropsiteMinDistance (const Fact& v, const location_type& l)
      {
        return symbol_type (token::DropsiteMinDistance, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EnableTimer (ActionType v, location_type l)
      {
        return symbol_type (token::EnableTimer, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EnableTimer (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::EnableTimer, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EnableWallPlacement (ActionType v, location_type l)
      {
        return symbol_type (token::EnableWallPlacement, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EnableWallPlacement (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::EnableWallPlacement, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EnemyBuildingsInTown (Fact v, location_type l)
      {
        return symbol_type (token::EnemyBuildingsInTown, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EnemyBuildingsInTown (const Fact& v, const location_type& l)
      {
        return symbol_type (token::EnemyBuildingsInTown, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EnemyCapturedRelics (Fact v, location_type l)
      {
        return symbol_type (token::EnemyCapturedRelics, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EnemyCapturedRelics (const Fact& v, const location_type& l)
      {
        return symbol_type (token::EnemyCapturedRelics, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EscrowAmount (Fact v, location_type l)
      {
        return symbol_type (token::EscrowAmount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EscrowAmount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::EscrowAmount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EventDetected (Fact v, location_type l)
      {
        return symbol_type (token::EventDetected, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EventDetected (const Fact& v, const location_type& l)
      {
        return symbol_type (token::EventDetected, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Falseval (Fact v, location_type l)
      {
        return symbol_type (token::Falseval, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Falseval (const Fact& v, const location_type& l)
      {
        return symbol_type (token::Falseval, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FoodAmount (Fact v, location_type l)
      {
        return symbol_type (token::FoodAmount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FoodAmount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::FoodAmount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GameTime (Fact v, location_type l)
      {
        return symbol_type (token::GameTime, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GameTime (const Fact& v, const location_type& l)
      {
        return symbol_type (token::GameTime, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GenerateRandomNumber (ActionType v, location_type l)
      {
        return symbol_type (token::GenerateRandomNumber, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GenerateRandomNumber (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::GenerateRandomNumber, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Goal (Fact v, location_type l)
      {
        return symbol_type (token::Goal, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Goal (const Fact& v, const location_type& l)
      {
        return symbol_type (token::Goal, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GoldAmount (Fact v, location_type l)
      {
        return symbol_type (token::GoldAmount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GoldAmount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::GoldAmount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HousingHeadroom (Fact v, location_type l)
      {
        return symbol_type (token::HousingHeadroom, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_HousingHeadroom (const Fact& v, const location_type& l)
      {
        return symbol_type (token::HousingHeadroom, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IdleFarmCount (Fact v, location_type l)
      {
        return symbol_type (token::IdleFarmCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IdleFarmCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::IdleFarmCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Log (ActionType v, location_type l)
      {
        return symbol_type (token::Log, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Log (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::Log, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LogTrace (ActionType v, location_type l)
      {
        return symbol_type (token::LogTrace, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LogTrace (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::LogTrace, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapSize (Fact v, location_type l)
      {
        return symbol_type (token::MapSize, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MapSize (const Fact& v, const location_type& l)
      {
        return symbol_type (token::MapSize, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapSizeTypeTiny (location_type l)
      {
        return symbol_type (token::MapSizeTypeTiny, std::move (l));
      }
#else
      static
      symbol_type
      make_MapSizeTypeTiny (const location_type& l)
      {
        return symbol_type (token::MapSizeTypeTiny, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapSizeTypeSmall (location_type l)
      {
        return symbol_type (token::MapSizeTypeSmall, std::move (l));
      }
#else
      static
      symbol_type
      make_MapSizeTypeSmall (const location_type& l)
      {
        return symbol_type (token::MapSizeTypeSmall, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapSizeTypeMedium (location_type l)
      {
        return symbol_type (token::MapSizeTypeMedium, std::move (l));
      }
#else
      static
      symbol_type
      make_MapSizeTypeMedium (const location_type& l)
      {
        return symbol_type (token::MapSizeTypeMedium, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapSizeTypeNormal (location_type l)
      {
        return symbol_type (token::MapSizeTypeNormal, std::move (l));
      }
#else
      static
      symbol_type
      make_MapSizeTypeNormal (const location_type& l)
      {
        return symbol_type (token::MapSizeTypeNormal, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapSizeTypeLarge (location_type l)
      {
        return symbol_type (token::MapSizeTypeLarge, std::move (l));
      }
#else
      static
      symbol_type
      make_MapSizeTypeLarge (const location_type& l)
      {
        return symbol_type (token::MapSizeTypeLarge, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapSizeTypeGiant (location_type l)
      {
        return symbol_type (token::MapSizeTypeGiant, std::move (l));
      }
#else
      static
      symbol_type
      make_MapSizeTypeGiant (const location_type& l)
      {
        return symbol_type (token::MapSizeTypeGiant, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapType (Fact v, location_type l)
      {
        return symbol_type (token::MapType, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MapType (const Fact& v, const location_type& l)
      {
        return symbol_type (token::MapType, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameArabia (location_type l)
      {
        return symbol_type (token::MapTypeNameArabia, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameArabia (const location_type& l)
      {
        return symbol_type (token::MapTypeNameArabia, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameArchipelago (location_type l)
      {
        return symbol_type (token::MapTypeNameArchipelago, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameArchipelago (const location_type& l)
      {
        return symbol_type (token::MapTypeNameArchipelago, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameBaltic (location_type l)
      {
        return symbol_type (token::MapTypeNameBaltic, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameBaltic (const location_type& l)
      {
        return symbol_type (token::MapTypeNameBaltic, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameBlackForest (location_type l)
      {
        return symbol_type (token::MapTypeNameBlackForest, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameBlackForest (const location_type& l)
      {
        return symbol_type (token::MapTypeNameBlackForest, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameCoastal (location_type l)
      {
        return symbol_type (token::MapTypeNameCoastal, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameCoastal (const location_type& l)
      {
        return symbol_type (token::MapTypeNameCoastal, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameContinental (location_type l)
      {
        return symbol_type (token::MapTypeNameContinental, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameContinental (const location_type& l)
      {
        return symbol_type (token::MapTypeNameContinental, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameCraterLake (location_type l)
      {
        return symbol_type (token::MapTypeNameCraterLake, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameCraterLake (const location_type& l)
      {
        return symbol_type (token::MapTypeNameCraterLake, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameFortress (location_type l)
      {
        return symbol_type (token::MapTypeNameFortress, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameFortress (const location_type& l)
      {
        return symbol_type (token::MapTypeNameFortress, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameGoldRush (location_type l)
      {
        return symbol_type (token::MapTypeNameGoldRush, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameGoldRush (const location_type& l)
      {
        return symbol_type (token::MapTypeNameGoldRush, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameHighland (location_type l)
      {
        return symbol_type (token::MapTypeNameHighland, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameHighland (const location_type& l)
      {
        return symbol_type (token::MapTypeNameHighland, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameIslands (location_type l)
      {
        return symbol_type (token::MapTypeNameIslands, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameIslands (const location_type& l)
      {
        return symbol_type (token::MapTypeNameIslands, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameMediterranean (location_type l)
      {
        return symbol_type (token::MapTypeNameMediterranean, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameMediterranean (const location_type& l)
      {
        return symbol_type (token::MapTypeNameMediterranean, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameMigration (location_type l)
      {
        return symbol_type (token::MapTypeNameMigration, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameMigration (const location_type& l)
      {
        return symbol_type (token::MapTypeNameMigration, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameRivers (location_type l)
      {
        return symbol_type (token::MapTypeNameRivers, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameRivers (const location_type& l)
      {
        return symbol_type (token::MapTypeNameRivers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameTeamIslands (location_type l)
      {
        return symbol_type (token::MapTypeNameTeamIslands, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameTeamIslands (const location_type& l)
      {
        return symbol_type (token::MapTypeNameTeamIslands, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MapTypeNameScenarioMap (location_type l)
      {
        return symbol_type (token::MapTypeNameScenarioMap, std::move (l));
      }
#else
      static
      symbol_type
      make_MapTypeNameScenarioMap (const location_type& l)
      {
        return symbol_type (token::MapTypeNameScenarioMap, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MilitaryPopulation (Fact v, location_type l)
      {
        return symbol_type (token::MilitaryPopulation, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MilitaryPopulation (const Fact& v, const location_type& l)
      {
        return symbol_type (token::MilitaryPopulation, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerComputer (Fact v, location_type l)
      {
        return symbol_type (token::PlayerComputer, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerComputer (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayerComputer, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerHuman (Fact v, location_type l)
      {
        return symbol_type (token::PlayerHuman, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerHuman (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayerHuman, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerInGame (Fact v, location_type l)
      {
        return symbol_type (token::PlayerInGame, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerInGame (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayerInGame, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumber (Fact v, location_type l)
      {
        return symbol_type (token::PlayerNumber, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumber (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayerNumber, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyAlly (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyAlly, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyAlly (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyAlly, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyComputer (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyComputer, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyComputer (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyComputer, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyComputerAlly (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyComputerAlly, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyComputerAlly (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyComputerAlly, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyComputerEnemy (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyComputerEnemy, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyComputerEnemy (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyComputerEnemy, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyComputerNeutral (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyComputerNeutral, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyComputerNeutral (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyComputerNeutral, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyEnemy (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyEnemy, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyEnemy (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyEnemy, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyHuman (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyHuman, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyHuman (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyHuman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyHumanAlly (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyHumanAlly, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyHumanAlly (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyHumanAlly, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyHumanEnemy (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyHumanEnemy, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyHumanEnemy (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyHumanEnemy, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyHumanNeutral (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyHumanNeutral, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyHumanNeutral (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyHumanNeutral, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeAnyNeutral (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeAnyNeutral, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeAnyNeutral (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeAnyNeutral, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeEveryAlly (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeEveryAlly, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeEveryAlly (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeEveryAlly, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeEveryComputer (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeEveryComputer, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeEveryComputer (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeEveryComputer, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeEveryEnemy (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeEveryEnemy, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeEveryEnemy (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeEveryEnemy, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeEveryHuman (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeEveryHuman, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeEveryHuman (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeEveryHuman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeEveryNeutral (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeEveryNeutral, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeEveryNeutral (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeEveryNeutral, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerNumberTypeMyPlayerNumber (location_type l)
      {
        return symbol_type (token::PlayerNumberTypeMyPlayerNumber, std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerNumberTypeMyPlayerNumber (const location_type& l)
      {
        return symbol_type (token::PlayerNumberTypeMyPlayerNumber, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerResigned (Fact v, location_type l)
      {
        return symbol_type (token::PlayerResigned, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerResigned (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayerResigned, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersBuildingCount (Fact v, location_type l)
      {
        return symbol_type (token::PlayersBuildingCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersBuildingCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersBuildingCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersBuildingTypeCount (Fact v, location_type l)
      {
        return symbol_type (token::PlayersBuildingTypeCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersBuildingTypeCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersBuildingTypeCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersCiv (Fact v, location_type l)
      {
        return symbol_type (token::PlayersCiv, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersCiv (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersCiv, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersCivilianPopulation (Fact v, location_type l)
      {
        return symbol_type (token::PlayersCivilianPopulation, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersCivilianPopulation (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersCivilianPopulation, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersCurrentAge (Fact v, location_type l)
      {
        return symbol_type (token::PlayersCurrentAge, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersCurrentAge (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersCurrentAge, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersCurrentAgeTime (Fact v, location_type l)
      {
        return symbol_type (token::PlayersCurrentAgeTime, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersCurrentAgeTime (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersCurrentAgeTime, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersMilitaryPopulation (Fact v, location_type l)
      {
        return symbol_type (token::PlayersMilitaryPopulation, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersMilitaryPopulation (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersMilitaryPopulation, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersPopulation (Fact v, location_type l)
      {
        return symbol_type (token::PlayersPopulation, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersPopulation (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersPopulation, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersScore (Fact v, location_type l)
      {
        return symbol_type (token::PlayersScore, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersScore (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersScore, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersStance (Fact v, location_type l)
      {
        return symbol_type (token::PlayersStance, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersStance (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersStance, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersTribute (Fact v, location_type l)
      {
        return symbol_type (token::PlayersTribute, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersTribute (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersTribute, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersTributeMemory (Fact v, location_type l)
      {
        return symbol_type (token::PlayersTributeMemory, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersTributeMemory (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersTributeMemory, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersUnitCount (Fact v, location_type l)
      {
        return symbol_type (token::PlayersUnitCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersUnitCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersUnitCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayersUnitTypeCount (Fact v, location_type l)
      {
        return symbol_type (token::PlayersUnitTypeCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayersUnitTypeCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayersUnitTypeCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PlayerValid (Fact v, location_type l)
      {
        return symbol_type (token::PlayerValid, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PlayerValid (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PlayerValid, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Population (Fact v, location_type l)
      {
        return symbol_type (token::Population, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Population (const Fact& v, const location_type& l)
      {
        return symbol_type (token::Population, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PopulationCap (Fact v, location_type l)
      {
        return symbol_type (token::PopulationCap, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PopulationCap (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PopulationCap, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PopulationHeadroom (Fact v, location_type l)
      {
        return symbol_type (token::PopulationHeadroom, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PopulationHeadroom (const Fact& v, const location_type& l)
      {
        return symbol_type (token::PopulationHeadroom, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RandomNumber (Fact v, location_type l)
      {
        return symbol_type (token::RandomNumber, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RandomNumber (const Fact& v, const location_type& l)
      {
        return symbol_type (token::RandomNumber, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RegicideGame (Fact v, location_type l)
      {
        return symbol_type (token::RegicideGame, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RegicideGame (const Fact& v, const location_type& l)
      {
        return symbol_type (token::RegicideGame, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ReleaseEscrow (ActionType v, location_type l)
      {
        return symbol_type (token::ReleaseEscrow, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ReleaseEscrow (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::ReleaseEscrow, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RelOpLessThan (location_type l)
      {
        return symbol_type (token::RelOpLessThan, std::move (l));
      }
#else
      static
      symbol_type
      make_RelOpLessThan (const location_type& l)
      {
        return symbol_type (token::RelOpLessThan, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RelOpLessOrEqual (location_type l)
      {
        return symbol_type (token::RelOpLessOrEqual, std::move (l));
      }
#else
      static
      symbol_type
      make_RelOpLessOrEqual (const location_type& l)
      {
        return symbol_type (token::RelOpLessOrEqual, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RelOpGreaterThan (location_type l)
      {
        return symbol_type (token::RelOpGreaterThan, std::move (l));
      }
#else
      static
      symbol_type
      make_RelOpGreaterThan (const location_type& l)
      {
        return symbol_type (token::RelOpGreaterThan, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RelOpGreaterOrEqual (location_type l)
      {
        return symbol_type (token::RelOpGreaterOrEqual, std::move (l));
      }
#else
      static
      symbol_type
      make_RelOpGreaterOrEqual (const location_type& l)
      {
        return symbol_type (token::RelOpGreaterOrEqual, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RelOpEqual (location_type l)
      {
        return symbol_type (token::RelOpEqual, std::move (l));
      }
#else
      static
      symbol_type
      make_RelOpEqual (const location_type& l)
      {
        return symbol_type (token::RelOpEqual, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RelOpNotEqual (location_type l)
      {
        return symbol_type (token::RelOpNotEqual, std::move (l));
      }
#else
      static
      symbol_type
      make_RelOpNotEqual (const location_type& l)
      {
        return symbol_type (token::RelOpNotEqual, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Research (ActionType v, location_type l)
      {
        return symbol_type (token::Research, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Research (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::Research, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchAvailable (Fact v, location_type l)
      {
        return symbol_type (token::ResearchAvailable, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchAvailable (const Fact& v, const location_type& l)
      {
        return symbol_type (token::ResearchAvailable, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchCompleted (Fact v, location_type l)
      {
        return symbol_type (token::ResearchCompleted, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchCompleted (const Fact& v, const location_type& l)
      {
        return symbol_type (token::ResearchCompleted, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiArbalest (location_type l)
      {
        return symbol_type (token::ResearchItemRiArbalest, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiArbalest (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiArbalest, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiCrossbow (location_type l)
      {
        return symbol_type (token::ResearchItemRiCrossbow, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiCrossbow (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiCrossbow, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteSkirmisher (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteSkirmisher, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteSkirmisher (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteSkirmisher, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHandCannon (location_type l)
      {
        return symbol_type (token::ResearchItemRiHandCannon, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHandCannon (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHandCannon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHeavyCavalryArcher (location_type l)
      {
        return symbol_type (token::ResearchItemRiHeavyCavalryArcher, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHeavyCavalryArcher (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHeavyCavalryArcher, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiChampion (location_type l)
      {
        return symbol_type (token::ResearchItemRiChampion, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiChampion (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiChampion, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteEagleWarrior (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteEagleWarrior, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteEagleWarrior (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteEagleWarrior, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHalberdier (location_type l)
      {
        return symbol_type (token::ResearchItemRiHalberdier, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHalberdier (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHalberdier, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiLongSwordsman (location_type l)
      {
        return symbol_type (token::ResearchItemRiLongSwordsman, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiLongSwordsman (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiLongSwordsman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiManAtArms (location_type l)
      {
        return symbol_type (token::ResearchItemRiManAtArms, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiManAtArms (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiManAtArms, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiParthianTactics (location_type l)
      {
        return symbol_type (token::ResearchItemRiParthianTactics, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiParthianTactics (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiParthianTactics, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiPikeman (location_type l)
      {
        return symbol_type (token::ResearchItemRiPikeman, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiPikeman (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiPikeman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiSquires (location_type l)
      {
        return symbol_type (token::ResearchItemRiSquires, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiSquires (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiSquires, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiThumbRing (location_type l)
      {
        return symbol_type (token::ResearchItemRiThumbRing, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiThumbRing (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiThumbRing, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiTracking (location_type l)
      {
        return symbol_type (token::ResearchItemRiTracking, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiTracking (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiTracking, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiTwoHandedSwordsman (location_type l)
      {
        return symbol_type (token::ResearchItemRiTwoHandedSwordsman, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiTwoHandedSwordsman (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiTwoHandedSwordsman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiBlastFurnace (location_type l)
      {
        return symbol_type (token::ResearchItemRiBlastFurnace, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiBlastFurnace (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiBlastFurnace, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiBodkinArrow (location_type l)
      {
        return symbol_type (token::ResearchItemRiBodkinArrow, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiBodkinArrow (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiBodkinArrow, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiBracer (location_type l)
      {
        return symbol_type (token::ResearchItemRiBracer, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiBracer (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiBracer, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiChainBarding (location_type l)
      {
        return symbol_type (token::ResearchItemRiChainBarding, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiChainBarding (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiChainBarding, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiChainMail (location_type l)
      {
        return symbol_type (token::ResearchItemRiChainMail, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiChainMail (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiChainMail, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiFletching (location_type l)
      {
        return symbol_type (token::ResearchItemRiFletching, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiFletching (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiFletching, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiForging (location_type l)
      {
        return symbol_type (token::ResearchItemRiForging, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiForging (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiForging, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiIronCasting (location_type l)
      {
        return symbol_type (token::ResearchItemRiIronCasting, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiIronCasting (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiIronCasting, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiLeatherArcherArmor (location_type l)
      {
        return symbol_type (token::ResearchItemRiLeatherArcherArmor, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiLeatherArcherArmor (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiLeatherArcherArmor, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiPaddedArcherArmor (location_type l)
      {
        return symbol_type (token::ResearchItemRiPaddedArcherArmor, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiPaddedArcherArmor (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiPaddedArcherArmor, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiPlateBarding (location_type l)
      {
        return symbol_type (token::ResearchItemRiPlateBarding, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiPlateBarding (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiPlateBarding, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiPlateMail (location_type l)
      {
        return symbol_type (token::ResearchItemRiPlateMail, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiPlateMail (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiPlateMail, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiRingArcherArmor (location_type l)
      {
        return symbol_type (token::ResearchItemRiRingArcherArmor, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiRingArcherArmor (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiRingArcherArmor, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiScaleBarding (location_type l)
      {
        return symbol_type (token::ResearchItemRiScaleBarding, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiScaleBarding (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiScaleBarding, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiScaleMail (location_type l)
      {
        return symbol_type (token::ResearchItemRiScaleMail, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiScaleMail (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiScaleMail, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiConscription (location_type l)
      {
        return symbol_type (token::ResearchItemRiConscription, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiConscription (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiConscription, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHoardings (location_type l)
      {
        return symbol_type (token::ResearchItemRiHoardings, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHoardings (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHoardings, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiSappers (location_type l)
      {
        return symbol_type (token::ResearchItemRiSappers, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiSappers (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiSappers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteBerserk (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteBerserk, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteBerserk (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteBerserk, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteCataphract (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteCataphract, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteCataphract (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteCataphract, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteChuKoNu (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteChuKoNu, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteChuKoNu (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteChuKoNu, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteHuskarl (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteHuskarl, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteHuskarl (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteHuskarl, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteJanissary (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteJanissary, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteJanissary (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteJanissary, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteLongbowman (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteLongbowman, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteLongbowman (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteLongbowman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteMameluke (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteMameluke, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteMameluke (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteMameluke, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteMangudai (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteMangudai, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteMangudai (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteMangudai, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteSamurai (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteSamurai, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteSamurai (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteSamurai, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteTeutonicKnight (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteTeutonicKnight, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteTeutonicKnight (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteTeutonicKnight, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteThrowingAxeman (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteThrowingAxeman, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteThrowingAxeman (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteThrowingAxeman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteWarElephant (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteWarElephant, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteWarElephant (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteWarElephant, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteWoadRaider (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteWoadRaider, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteWoadRaider (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteWoadRaider, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiMyUniqueEliteUnit (location_type l)
      {
        return symbol_type (token::ResearchItemRiMyUniqueEliteUnit, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiMyUniqueEliteUnit (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiMyUniqueEliteUnit, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiMyUniqueResearch (location_type l)
      {
        return symbol_type (token::ResearchItemRiMyUniqueResearch, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiMyUniqueResearch (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiMyUniqueResearch, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiCannonGalleon (location_type l)
      {
        return symbol_type (token::ResearchItemRiCannonGalleon, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiCannonGalleon (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiCannonGalleon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiCareening (location_type l)
      {
        return symbol_type (token::ResearchItemRiCareening, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiCareening (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiCareening, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiDeckGuns (location_type l)
      {
        return symbol_type (token::ResearchItemRiDeckGuns, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiDeckGuns (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiDeckGuns, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiDryDock (location_type l)
      {
        return symbol_type (token::ResearchItemRiDryDock, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiDryDock (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiDryDock, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiEliteLongboat (location_type l)
      {
        return symbol_type (token::ResearchItemRiEliteLongboat, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiEliteLongboat (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiEliteLongboat, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiFastFireShip (location_type l)
      {
        return symbol_type (token::ResearchItemRiFastFireShip, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiFastFireShip (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiFastFireShip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiGalleon (location_type l)
      {
        return symbol_type (token::ResearchItemRiGalleon, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiGalleon (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiGalleon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHeavyDemolitionShip (location_type l)
      {
        return symbol_type (token::ResearchItemRiHeavyDemolitionShip, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHeavyDemolitionShip (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHeavyDemolitionShip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiShipwright (location_type l)
      {
        return symbol_type (token::ResearchItemRiShipwright, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiShipwright (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiShipwright, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiWarGalley (location_type l)
      {
        return symbol_type (token::ResearchItemRiWarGalley, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiWarGalley (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiWarGalley, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiBowSaw (location_type l)
      {
        return symbol_type (token::ResearchItemRiBowSaw, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiBowSaw (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiBowSaw, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiDoubleBitAxe (location_type l)
      {
        return symbol_type (token::ResearchItemRiDoubleBitAxe, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiDoubleBitAxe (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiDoubleBitAxe, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiTwoManSaw (location_type l)
      {
        return symbol_type (token::ResearchItemRiTwoManSaw, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiTwoManSaw (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiTwoManSaw, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiBanking (location_type l)
      {
        return symbol_type (token::ResearchItemRiBanking, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiBanking (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiBanking, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiCaravan (location_type l)
      {
        return symbol_type (token::ResearchItemRiCaravan, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiCaravan (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiCaravan, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiCartography (location_type l)
      {
        return symbol_type (token::ResearchItemRiCartography, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiCartography (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiCartography, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiCoinage (location_type l)
      {
        return symbol_type (token::ResearchItemRiCoinage, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiCoinage (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiCoinage, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiGuilds (location_type l)
      {
        return symbol_type (token::ResearchItemRiGuilds, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiGuilds (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiGuilds, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiCropRotation (location_type l)
      {
        return symbol_type (token::ResearchItemRiCropRotation, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiCropRotation (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiCropRotation, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHeavyPlow (location_type l)
      {
        return symbol_type (token::ResearchItemRiHeavyPlow, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHeavyPlow (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHeavyPlow, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHorseCollar (location_type l)
      {
        return symbol_type (token::ResearchItemRiHorseCollar, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHorseCollar (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHorseCollar, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiGoldMining (location_type l)
      {
        return symbol_type (token::ResearchItemRiGoldMining, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiGoldMining (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiGoldMining, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiGoldShaftMining (location_type l)
      {
        return symbol_type (token::ResearchItemRiGoldShaftMining, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiGoldShaftMining (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiGoldShaftMining, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiStoneMining (location_type l)
      {
        return symbol_type (token::ResearchItemRiStoneMining, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiStoneMining (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiStoneMining, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiStoneShaftMining (location_type l)
      {
        return symbol_type (token::ResearchItemRiStoneShaftMining, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiStoneShaftMining (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiStoneShaftMining, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiAtonement (location_type l)
      {
        return symbol_type (token::ResearchItemRiAtonement, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiAtonement (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiAtonement, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiBlockPrinting (location_type l)
      {
        return symbol_type (token::ResearchItemRiBlockPrinting, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiBlockPrinting (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiBlockPrinting, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiFaith (location_type l)
      {
        return symbol_type (token::ResearchItemRiFaith, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiFaith (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiFaith, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiFervor (location_type l)
      {
        return symbol_type (token::ResearchItemRiFervor, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiFervor (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiFervor, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHerbalMedicine (location_type l)
      {
        return symbol_type (token::ResearchItemRiHerbalMedicine, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHerbalMedicine (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHerbalMedicine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHeresy (location_type l)
      {
        return symbol_type (token::ResearchItemRiHeresy, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHeresy (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHeresy, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiIllumination (location_type l)
      {
        return symbol_type (token::ResearchItemRiIllumination, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiIllumination (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiIllumination, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiRedemption (location_type l)
      {
        return symbol_type (token::ResearchItemRiRedemption, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiRedemption (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiRedemption, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiSanctity (location_type l)
      {
        return symbol_type (token::ResearchItemRiSanctity, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiSanctity (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiSanctity, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiTheocracy (location_type l)
      {
        return symbol_type (token::ResearchItemRiTheocracy, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiTheocracy (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiTheocracy, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiBombardCannon (location_type l)
      {
        return symbol_type (token::ResearchItemRiBombardCannon, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiBombardCannon (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiBombardCannon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiCappedRam (location_type l)
      {
        return symbol_type (token::ResearchItemRiCappedRam, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiCappedRam (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiCappedRam, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHeavyScorpion (location_type l)
      {
        return symbol_type (token::ResearchItemRiHeavyScorpion, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHeavyScorpion (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHeavyScorpion, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiOnager (location_type l)
      {
        return symbol_type (token::ResearchItemRiOnager, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiOnager (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiOnager, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiScorpion (location_type l)
      {
        return symbol_type (token::ResearchItemRiScorpion, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiScorpion (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiScorpion, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiSiegeOnager (location_type l)
      {
        return symbol_type (token::ResearchItemRiSiegeOnager, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiSiegeOnager (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiSiegeOnager, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiSiegeRam (location_type l)
      {
        return symbol_type (token::ResearchItemRiSiegeRam, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiSiegeRam (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiSiegeRam, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiBloodlines (location_type l)
      {
        return symbol_type (token::ResearchItemRiBloodlines, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiBloodlines (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiBloodlines, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiCavalier (location_type l)
      {
        return symbol_type (token::ResearchItemRiCavalier, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiCavalier (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiCavalier, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHeavyCamel (location_type l)
      {
        return symbol_type (token::ResearchItemRiHeavyCamel, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHeavyCamel (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHeavyCamel, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHusbandry (location_type l)
      {
        return symbol_type (token::ResearchItemRiHusbandry, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHusbandry (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHusbandry, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHussar (location_type l)
      {
        return symbol_type (token::ResearchItemRiHussar, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHussar (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHussar, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiLightCavalry (location_type l)
      {
        return symbol_type (token::ResearchItemRiLightCavalry, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiLightCavalry (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiLightCavalry, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiPaladin (location_type l)
      {
        return symbol_type (token::ResearchItemRiPaladin, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiPaladin (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiPaladin, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHandCart (location_type l)
      {
        return symbol_type (token::ResearchItemRiHandCart, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHandCart (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHandCart, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiLoom (location_type l)
      {
        return symbol_type (token::ResearchItemRiLoom, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiLoom (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiLoom, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiTownPatrol (location_type l)
      {
        return symbol_type (token::ResearchItemRiTownPatrol, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiTownPatrol (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiTownPatrol, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiTownWatch (location_type l)
      {
        return symbol_type (token::ResearchItemRiTownWatch, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiTownWatch (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiTownWatch, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiWheelBarrow (location_type l)
      {
        return symbol_type (token::ResearchItemRiWheelBarrow, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiWheelBarrow (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiWheelBarrow, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiArchitecture (location_type l)
      {
        return symbol_type (token::ResearchItemRiArchitecture, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiArchitecture (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiArchitecture, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiBallistics (location_type l)
      {
        return symbol_type (token::ResearchItemRiBallistics, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiBallistics (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiBallistics, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiBombardTower (location_type l)
      {
        return symbol_type (token::ResearchItemRiBombardTower, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiBombardTower (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiBombardTower, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiChemistry (location_type l)
      {
        return symbol_type (token::ResearchItemRiChemistry, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiChemistry (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiChemistry, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiFortifiedWall (location_type l)
      {
        return symbol_type (token::ResearchItemRiFortifiedWall, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiFortifiedWall (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiFortifiedWall, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiGuardTower (location_type l)
      {
        return symbol_type (token::ResearchItemRiGuardTower, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiGuardTower (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiGuardTower, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiHeatedShot (location_type l)
      {
        return symbol_type (token::ResearchItemRiHeatedShot, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiHeatedShot (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiHeatedShot, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiKeep (location_type l)
      {
        return symbol_type (token::ResearchItemRiKeep, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiKeep (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiKeep, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiMasonry (location_type l)
      {
        return symbol_type (token::ResearchItemRiMasonry, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiMasonry (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiMasonry, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiMurderHoles (location_type l)
      {
        return symbol_type (token::ResearchItemRiMurderHoles, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiMurderHoles (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiMurderHoles, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiSiegeEngineers (location_type l)
      {
        return symbol_type (token::ResearchItemRiSiegeEngineers, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiSiegeEngineers (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiSiegeEngineers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemRiStonecutting (location_type l)
      {
        return symbol_type (token::ResearchItemRiStonecutting, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemRiStonecutting (const location_type& l)
      {
        return symbol_type (token::ResearchItemRiStonecutting, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemMyUniqueUnitUpgrade (location_type l)
      {
        return symbol_type (token::ResearchItemMyUniqueUnitUpgrade, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemMyUniqueUnitUpgrade (const location_type& l)
      {
        return symbol_type (token::ResearchItemMyUniqueUnitUpgrade, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResearchItemMyUniqueResearch (location_type l)
      {
        return symbol_type (token::ResearchItemMyUniqueResearch, std::move (l));
      }
#else
      static
      symbol_type
      make_ResearchItemMyUniqueResearch (const location_type& l)
      {
        return symbol_type (token::ResearchItemMyUniqueResearch, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Resign (ActionType v, location_type l)
      {
        return symbol_type (token::Resign, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Resign (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::Resign, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ResourceFound (Fact v, location_type l)
      {
        return symbol_type (token::ResourceFound, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ResourceFound (const Fact& v, const location_type& l)
      {
        return symbol_type (token::ResourceFound, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SellCommodity (ActionType v, location_type l)
      {
        return symbol_type (token::SellCommodity, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SellCommodity (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::SellCommodity, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SetDifficultyParameter (ActionType v, location_type l)
      {
        return symbol_type (token::SetDifficultyParameter, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SetDifficultyParameter (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::SetDifficultyParameter, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SetDoctrine (ActionType v, location_type l)
      {
        return symbol_type (token::SetDoctrine, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SetDoctrine (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::SetDoctrine, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SetEscrowPercentage (ActionType v, location_type l)
      {
        return symbol_type (token::SetEscrowPercentage, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SetEscrowPercentage (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::SetEscrowPercentage, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SetGoal (ActionType v, location_type l)
      {
        return symbol_type (token::SetGoal, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SetGoal (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::SetGoal, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SetSharedGoal (ActionType v, location_type l)
      {
        return symbol_type (token::SetSharedGoal, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SetSharedGoal (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::SetSharedGoal, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SetSignal (ActionType v, location_type l)
      {
        return symbol_type (token::SetSignal, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SetSignal (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::SetSignal, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SetStance (ActionType v, location_type l)
      {
        return symbol_type (token::SetStance, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SetStance (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::SetStance, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SetStrategicNumber (ActionType v, location_type l)
      {
        return symbol_type (token::SetStrategicNumber, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SetStrategicNumber (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::SetStrategicNumber, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SharedGoal (Fact v, location_type l)
      {
        return symbol_type (token::SharedGoal, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SharedGoal (const Fact& v, const location_type& l)
      {
        return symbol_type (token::SharedGoal, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SheepAndForageTooFar (Fact v, location_type l)
      {
        return symbol_type (token::SheepAndForageTooFar, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SheepAndForageTooFar (const Fact& v, const location_type& l)
      {
        return symbol_type (token::SheepAndForageTooFar, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SoldierCount (Fact v, location_type l)
      {
        return symbol_type (token::SoldierCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SoldierCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::SoldierCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Spy (ActionType v, location_type l)
      {
        return symbol_type (token::Spy, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Spy (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::Spy, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StanceToward (Fact v, location_type l)
      {
        return symbol_type (token::StanceToward, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_StanceToward (const Fact& v, const location_type& l)
      {
        return symbol_type (token::StanceToward, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StartingAge (Fact v, location_type l)
      {
        return symbol_type (token::StartingAge, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_StartingAge (const Fact& v, const location_type& l)
      {
        return symbol_type (token::StartingAge, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StartingResources (Fact v, location_type l)
      {
        return symbol_type (token::StartingResources, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_StartingResources (const Fact& v, const location_type& l)
      {
        return symbol_type (token::StartingResources, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StartingResourcesTypeLowResources (location_type l)
      {
        return symbol_type (token::StartingResourcesTypeLowResources, std::move (l));
      }
#else
      static
      symbol_type
      make_StartingResourcesTypeLowResources (const location_type& l)
      {
        return symbol_type (token::StartingResourcesTypeLowResources, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StartingResourcesTypeMediumResources (location_type l)
      {
        return symbol_type (token::StartingResourcesTypeMediumResources, std::move (l));
      }
#else
      static
      symbol_type
      make_StartingResourcesTypeMediumResources (const location_type& l)
      {
        return symbol_type (token::StartingResourcesTypeMediumResources, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StartingResourcesTypeHighResources (location_type l)
      {
        return symbol_type (token::StartingResourcesTypeHighResources, std::move (l));
      }
#else
      static
      symbol_type
      make_StartingResourcesTypeHighResources (const location_type& l)
      {
        return symbol_type (token::StartingResourcesTypeHighResources, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StoneAmount (Fact v, location_type l)
      {
        return symbol_type (token::StoneAmount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_StoneAmount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::StoneAmount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumber (Fact v, location_type l)
      {
        return symbol_type (token::StrategicNumber, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumber (const Fact& v, const location_type& l)
      {
        return symbol_type (token::StrategicNumber, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnPercentCivilianExplorers (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentCivilianExplorers, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnPercentCivilianExplorers (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentCivilianExplorers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnPercentCivilianBuilders (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentCivilianBuilders, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnPercentCivilianBuilders (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentCivilianBuilders, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnPercentCivilianGatherers (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentCivilianGatherers, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnPercentCivilianGatherers (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentCivilianGatherers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnCapCivilianExplorers (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnCapCivilianExplorers, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnCapCivilianExplorers (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnCapCivilianExplorers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnCapCivilianBuilders (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnCapCivilianBuilders, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnCapCivilianBuilders (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnCapCivilianBuilders, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnCapCivilianGatherers (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnCapCivilianGatherers, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnCapCivilianGatherers (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnCapCivilianGatherers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumAttackGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumAttackGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumAttackGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumAttackGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTotalNumberExplorers (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTotalNumberExplorers, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTotalNumberExplorers (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTotalNumberExplorers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnPercentEnemySightedResponse (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentEnemySightedResponse, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnPercentEnemySightedResponse (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentEnemySightedResponse, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnEnemySightedResponseDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnEnemySightedResponseDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnEnemySightedResponseDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnEnemySightedResponseDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnSentryDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnSentryDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnSentryDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnSentryDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnRelicReturnDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnRelicReturnDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnRelicReturnDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnRelicReturnDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumDefendGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumDefendGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumDefendGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumDefendGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumAttackGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumAttackGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumAttackGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumAttackGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumDefendGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumDefendGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumDefendGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumDefendGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumPeaceLikeLevel (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumPeaceLikeLevel, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumPeaceLikeLevel (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumPeaceLikeLevel, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnPercentExplorationRequired (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentExplorationRequired, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnPercentExplorationRequired (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentExplorationRequired, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnZeroPriorityDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnZeroPriorityDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnZeroPriorityDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnZeroPriorityDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumCivilianExplorers (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumCivilianExplorers, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumCivilianExplorers (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumCivilianExplorers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnNumberAttackGroups (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberAttackGroups, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnNumberAttackGroups (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberAttackGroups, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnNumberDefendGroups (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberDefendGroups, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnNumberDefendGroups (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberDefendGroups, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnAttackGroupGatherSpacing (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackGroupGatherSpacing, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnAttackGroupGatherSpacing (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackGroupGatherSpacing, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnNumberExploreGroups (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberExploreGroups, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnNumberExploreGroups (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberExploreGroups, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumExploreGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumExploreGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumExploreGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumExploreGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumExploreGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumExploreGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumExploreGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumExploreGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnGoldDefendPriority (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnGoldDefendPriority, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnGoldDefendPriority (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnGoldDefendPriority, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnStoneDefendPriority (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnStoneDefendPriority, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnStoneDefendPriority (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnStoneDefendPriority, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnForageDefendPriority (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnForageDefendPriority, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnForageDefendPriority (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnForageDefendPriority, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnRelicDefendPriority (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnRelicDefendPriority, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnRelicDefendPriority (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnRelicDefendPriority, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTownDefendPriority (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTownDefendPriority, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTownDefendPriority (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTownDefendPriority, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnDefenseDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnDefenseDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnDefenseDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnDefenseDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnNumberBoatAttackGroups (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberBoatAttackGroups, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnNumberBoatAttackGroups (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberBoatAttackGroups, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumBoatAttackGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumBoatAttackGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumBoatAttackGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumBoatAttackGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumBoatAttackGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumBoatAttackGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumBoatAttackGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumBoatAttackGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnNumberBoatExploreGroups (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberBoatExploreGroups, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnNumberBoatExploreGroups (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberBoatExploreGroups, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumBoatExploreGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumBoatExploreGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumBoatExploreGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumBoatExploreGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumBoatExploreGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumBoatExploreGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumBoatExploreGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumBoatExploreGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnNumberBoatDefendGroups (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberBoatDefendGroups, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnNumberBoatDefendGroups (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberBoatDefendGroups, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumBoatDefendGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumBoatDefendGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumBoatDefendGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumBoatDefendGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumBoatDefendGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumBoatDefendGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumBoatDefendGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumBoatDefendGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnDockDefendPriority (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnDockDefendPriority, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnDockDefendPriority (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnDockDefendPriority, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnSentryDistanceVariation (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnSentryDistanceVariation, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnSentryDistanceVariation (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnSentryDistanceVariation, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumTownSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumTownSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumTownSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumTownSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumTownSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumTownSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumTownSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumTownSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnGroupCommanderSelectionMethod (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnGroupCommanderSelectionMethod, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnGroupCommanderSelectionMethod (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnGroupCommanderSelectionMethod, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnConsecutiveIdleUnitLimit (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnConsecutiveIdleUnitLimit, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnConsecutiveIdleUnitLimit (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnConsecutiveIdleUnitLimit, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationHitpoints (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationHitpoints, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationHitpoints (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationHitpoints, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationDamageCapability (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationDamageCapability, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationDamageCapability (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationDamageCapability, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationKills (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationKills, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationKills (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationKills, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationAllyProximity (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationAllyProximity, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationAllyProximity (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationAllyProximity, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationRof (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationRof, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationRof (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationRof, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationRandomness (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationRandomness, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationRandomness (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationRandomness, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnCampMaxDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnCampMaxDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnCampMaxDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnCampMaxDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMillMaxDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMillMaxDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMillMaxDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMillMaxDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationAttackAttempts (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationAttackAttempts, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationAttackAttempts (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationAttackAttempts, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationRange (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationRange, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationRange (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationRange, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnDefendOverlapDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnDefendOverlapDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnDefendOverlapDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnDefendOverlapDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnScaleMinimumAttackGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnScaleMinimumAttackGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnScaleMinimumAttackGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnScaleMinimumAttackGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnScaleMaximumAttackGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnScaleMaximumAttackGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnScaleMaximumAttackGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnScaleMaximumAttackGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnAttackGroupSizeRandomness (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackGroupSizeRandomness, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnAttackGroupSizeRandomness (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackGroupSizeRandomness, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnScalingFrequency (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnScalingFrequency, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnScalingFrequency (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnScalingFrequency, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumGaiaAttackResponse (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumGaiaAttackResponse, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumGaiaAttackResponse (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumGaiaAttackResponse, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnBuildFrequency (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnBuildFrequency, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnBuildFrequency (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnBuildFrequency, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnAttackSeparationTimeRandomness (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackSeparationTimeRandomness, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnAttackSeparationTimeRandomness (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackSeparationTimeRandomness, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnAttackIntelligence (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackIntelligence, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnAttackIntelligence (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackIntelligence, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnInitialAttackDelay (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnInitialAttackDelay, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnInitialAttackDelay (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnInitialAttackDelay, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnSaveScenarioInformation (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnSaveScenarioInformation, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnSaveScenarioInformation (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnSaveScenarioInformation, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnSpecialAttackType1 (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnSpecialAttackType1, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnSpecialAttackType1 (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnSpecialAttackType1, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnSpecialAttackInfluence1 (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnSpecialAttackInfluence1, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnSpecialAttackInfluence1 (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnSpecialAttackInfluence1, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumWaterBodySizeForDock (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumWaterBodySizeForDock, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumWaterBodySizeForDock (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumWaterBodySizeForDock, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnNumberBuildAttemptsBeforeSkip (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberBuildAttemptsBeforeSkip, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnNumberBuildAttemptsBeforeSkip (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberBuildAttemptsBeforeSkip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaxSkipsPerAttempt (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaxSkipsPerAttempt, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaxSkipsPerAttempt (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaxSkipsPerAttempt, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnFoodGathererPercentage (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnFoodGathererPercentage, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnFoodGathererPercentage (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnFoodGathererPercentage, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnGoldGathererPercentage (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnGoldGathererPercentage, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnGoldGathererPercentage (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnGoldGathererPercentage, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnStoneGathererPercentage (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnStoneGathererPercentage, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnStoneGathererPercentage (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnStoneGathererPercentage, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnWoodGathererPercentage (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnWoodGathererPercentage, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnWoodGathererPercentage (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnWoodGathererPercentage, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationContinent (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationContinent, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationContinent (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationContinent, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationSiegeWeapon (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationSiegeWeapon, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationSiegeWeapon (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationSiegeWeapon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnGroupLeaderDefenseDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnGroupLeaderDefenseDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnGroupLeaderDefenseDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnGroupLeaderDefenseDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnInitialAttackDelayType (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnInitialAttackDelayType, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnInitialAttackDelayType (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnInitialAttackDelayType, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnBlotExplorationMap (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnBlotExplorationMap, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnBlotExplorationMap (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnBlotExplorationMap, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnBlotSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnBlotSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnBlotSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnBlotSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnIntelligentGathering (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnIntelligentGathering, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnIntelligentGathering (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnIntelligentGathering, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTaskUngroupedSoldiers (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTaskUngroupedSoldiers, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTaskUngroupedSoldiers (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTaskUngroupedSoldiers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationBoat (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationBoat, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationBoat (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationBoat, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnNumberEnemyObjectsRequired (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberEnemyObjectsRequired, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnNumberEnemyObjectsRequired (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberEnemyObjectsRequired, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnNumberMaxSkipCycles (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberMaxSkipCycles, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnNumberMaxSkipCycles (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberMaxSkipCycles, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnRetaskGatherAmount (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnRetaskGatherAmount, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnRetaskGatherAmount (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnRetaskGatherAmount, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaxRetaskGatherAmount (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaxRetaskGatherAmount, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaxRetaskGatherAmount (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaxRetaskGatherAmount, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaxBuildPlanGathererPercentage (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaxBuildPlanGathererPercentage, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaxBuildPlanGathererPercentage (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaxBuildPlanGathererPercentage, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnFoodDropsiteDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnFoodDropsiteDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnFoodDropsiteDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnFoodDropsiteDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnWoodDropsiteDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnWoodDropsiteDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnWoodDropsiteDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnWoodDropsiteDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnStoneDropsiteDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnStoneDropsiteDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnStoneDropsiteDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnStoneDropsiteDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnGoldDropsiteDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnGoldDropsiteDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnGoldDropsiteDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnGoldDropsiteDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnInitialExplorationRequired (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnInitialExplorationRequired, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnInitialExplorationRequired (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnInitialExplorationRequired, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnRandomPlacementFactor (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnRandomPlacementFactor, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnRandomPlacementFactor (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnRandomPlacementFactor, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnRequiredForestTiles (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnRequiredForestTiles, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnRequiredForestTiles (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnRequiredForestTiles, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnAttackDiplomacyImpact (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackDiplomacyImpact, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnAttackDiplomacyImpact (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackDiplomacyImpact, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnPercentHalfExploration (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentHalfExploration, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnPercentHalfExploration (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentHalfExploration, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationTimeKillRatio (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationTimeKillRatio, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationTimeKillRatio (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationTimeKillRatio, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationInProgress (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationInProgress, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTargetEvaluationInProgress (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTargetEvaluationInProgress, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnAttackWinningPlayer (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackWinningPlayer, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnAttackWinningPlayer (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackWinningPlayer, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnCoopShareInformation (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnCoopShareInformation, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnCoopShareInformation (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnCoopShareInformation, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnAttackWinningPlayerFactor (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackWinningPlayerFactor, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnAttackWinningPlayerFactor (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnAttackWinningPlayerFactor, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnCoopShareAttacking (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnCoopShareAttacking, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnCoopShareAttacking (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnCoopShareAttacking, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnCoopShareAttackingInterval (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnCoopShareAttackingInterval, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnCoopShareAttackingInterval (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnCoopShareAttackingInterval, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnPercentageExploreExterminators (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentageExploreExterminators, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnPercentageExploreExterminators (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentageExploreExterminators, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnTrackPlayerHistory (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnTrackPlayerHistory, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnTrackPlayerHistory (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnTrackPlayerHistory, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumDropsiteBuffer (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumDropsiteBuffer, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumDropsiteBuffer (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumDropsiteBuffer, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnUseByTypeMaxGathering (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnUseByTypeMaxGathering, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnUseByTypeMaxGathering (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnUseByTypeMaxGathering, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumBoarHuntGroupSize (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumBoarHuntGroupSize, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumBoarHuntGroupSize (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumBoarHuntGroupSize, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMinimumAmountForTrading (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumAmountForTrading, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMinimumAmountForTrading (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMinimumAmountForTrading, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnEasiestReactionPercentage (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnEasiestReactionPercentage, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnEasiestReactionPercentage (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnEasiestReactionPercentage, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnEasierReactionPercentage (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnEasierReactionPercentage, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnEasierReactionPercentage (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnEasierReactionPercentage, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnHitsBeforeAllianceChange (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnHitsBeforeAllianceChange, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnHitsBeforeAllianceChange (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnHitsBeforeAllianceChange, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnAllowCivilianDefense (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnAllowCivilianDefense, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnAllowCivilianDefense (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnAllowCivilianDefense, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnNumberForwardBuilders (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberForwardBuilders, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnNumberForwardBuilders (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnNumberForwardBuilders, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnPercentAttackSoldiers (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentAttackSoldiers, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnPercentAttackSoldiers (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentAttackSoldiers, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnPercentAttackBoats (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentAttackBoats, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnPercentAttackBoats (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnPercentAttackBoats, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnDoNotScaleForDifficultyLevel (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnDoNotScaleForDifficultyLevel, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnDoNotScaleForDifficultyLevel (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnDoNotScaleForDifficultyLevel, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnGroupFormDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnGroupFormDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnGroupFormDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnGroupFormDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnIgnoreAttackGroupUnderAttack (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnIgnoreAttackGroupUnderAttack, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnIgnoreAttackGroupUnderAttack (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnIgnoreAttackGroupUnderAttack, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnGatherDefenseUnits (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnGatherDefenseUnits, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnGatherDefenseUnits (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnGatherDefenseUnits, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumWoodDropDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumWoodDropDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumWoodDropDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumWoodDropDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumFoodDropDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumFoodDropDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumFoodDropDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumFoodDropDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumHuntDropDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumHuntDropDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumHuntDropDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumHuntDropDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumFishBoatDropDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumFishBoatDropDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumFishBoatDropDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumFishBoatDropDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumGoldDropDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumGoldDropDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumGoldDropDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumGoldDropDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnMaximumStoneDropDistance (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumStoneDropDistance, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnMaximumStoneDropDistance (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnMaximumStoneDropDistance, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnGatherIdleSoldiersAtCenter (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnGatherIdleSoldiersAtCenter, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnGatherIdleSoldiersAtCenter (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnGatherIdleSoldiersAtCenter, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_StrategicNumberNameSnGarrisonRams (location_type l)
      {
        return symbol_type (token::StrategicNumberNameSnGarrisonRams, std::move (l));
      }
#else
      static
      symbol_type
      make_StrategicNumberNameSnGarrisonRams (const location_type& l)
      {
        return symbol_type (token::StrategicNumberNameSnGarrisonRams, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Taunt (ActionType v, location_type l)
      {
        return symbol_type (token::Taunt, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Taunt (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::Taunt, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TauntDetected (Fact v, location_type l)
      {
        return symbol_type (token::TauntDetected, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TauntDetected (const Fact& v, const location_type& l)
      {
        return symbol_type (token::TauntDetected, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TauntUsingRange (ActionType v, location_type l)
      {
        return symbol_type (token::TauntUsingRange, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TauntUsingRange (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::TauntUsingRange, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TimerTriggered (Fact v, location_type l)
      {
        return symbol_type (token::TimerTriggered, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TimerTriggered (const Fact& v, const location_type& l)
      {
        return symbol_type (token::TimerTriggered, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TownUnderAttack (Fact v, location_type l)
      {
        return symbol_type (token::TownUnderAttack, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TownUnderAttack (const Fact& v, const location_type& l)
      {
        return symbol_type (token::TownUnderAttack, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Train (ActionType v, location_type l)
      {
        return symbol_type (token::Train, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Train (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::Train, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TributeToPlayer (ActionType v, location_type l)
      {
        return symbol_type (token::TributeToPlayer, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TributeToPlayer (const ActionType& v, const location_type& l)
      {
        return symbol_type (token::TributeToPlayer, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_Trueval (Fact v, location_type l)
      {
        return symbol_type (token::Trueval, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_Trueval (const Fact& v, const location_type& l)
      {
        return symbol_type (token::Trueval, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitArbalest (location_type l)
      {
        return symbol_type (token::UnitArbalest, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitArbalest (const location_type& l)
      {
        return symbol_type (token::UnitArbalest, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitArcher (location_type l)
      {
        return symbol_type (token::UnitArcher, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitArcher (const location_type& l)
      {
        return symbol_type (token::UnitArcher, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCavalryArcher (location_type l)
      {
        return symbol_type (token::UnitCavalryArcher, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCavalryArcher (const location_type& l)
      {
        return symbol_type (token::UnitCavalryArcher, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCrossbowman (location_type l)
      {
        return symbol_type (token::UnitCrossbowman, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCrossbowman (const location_type& l)
      {
        return symbol_type (token::UnitCrossbowman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteSkirmisher (location_type l)
      {
        return symbol_type (token::UnitEliteSkirmisher, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteSkirmisher (const location_type& l)
      {
        return symbol_type (token::UnitEliteSkirmisher, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitHandCannoneer (location_type l)
      {
        return symbol_type (token::UnitHandCannoneer, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitHandCannoneer (const location_type& l)
      {
        return symbol_type (token::UnitHandCannoneer, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitHeavyCavalryArcher (location_type l)
      {
        return symbol_type (token::UnitHeavyCavalryArcher, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitHeavyCavalryArcher (const location_type& l)
      {
        return symbol_type (token::UnitHeavyCavalryArcher, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitSkirmisher (location_type l)
      {
        return symbol_type (token::UnitSkirmisher, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitSkirmisher (const location_type& l)
      {
        return symbol_type (token::UnitSkirmisher, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitChampion (location_type l)
      {
        return symbol_type (token::UnitChampion, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitChampion (const location_type& l)
      {
        return symbol_type (token::UnitChampion, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEagleWarrior (location_type l)
      {
        return symbol_type (token::UnitEagleWarrior, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEagleWarrior (const location_type& l)
      {
        return symbol_type (token::UnitEagleWarrior, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteEagleWarrior (location_type l)
      {
        return symbol_type (token::UnitEliteEagleWarrior, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteEagleWarrior (const location_type& l)
      {
        return symbol_type (token::UnitEliteEagleWarrior, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitHalberdier (location_type l)
      {
        return symbol_type (token::UnitHalberdier, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitHalberdier (const location_type& l)
      {
        return symbol_type (token::UnitHalberdier, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitLongSwordsman (location_type l)
      {
        return symbol_type (token::UnitLongSwordsman, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitLongSwordsman (const location_type& l)
      {
        return symbol_type (token::UnitLongSwordsman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitManAtArms (location_type l)
      {
        return symbol_type (token::UnitManAtArms, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitManAtArms (const location_type& l)
      {
        return symbol_type (token::UnitManAtArms, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMilitiaman (location_type l)
      {
        return symbol_type (token::UnitMilitiaman, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMilitiaman (const location_type& l)
      {
        return symbol_type (token::UnitMilitiaman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitPikeman (location_type l)
      {
        return symbol_type (token::UnitPikeman, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitPikeman (const location_type& l)
      {
        return symbol_type (token::UnitPikeman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitSpearman (location_type l)
      {
        return symbol_type (token::UnitSpearman, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitSpearman (const location_type& l)
      {
        return symbol_type (token::UnitSpearman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTwoHandedSwordsman (location_type l)
      {
        return symbol_type (token::UnitTwoHandedSwordsman, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTwoHandedSwordsman (const location_type& l)
      {
        return symbol_type (token::UnitTwoHandedSwordsman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitBerserk (location_type l)
      {
        return symbol_type (token::UnitBerserk, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitBerserk (const location_type& l)
      {
        return symbol_type (token::UnitBerserk, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCataphract (location_type l)
      {
        return symbol_type (token::UnitCataphract, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCataphract (const location_type& l)
      {
        return symbol_type (token::UnitCataphract, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitChuKoNu (location_type l)
      {
        return symbol_type (token::UnitChuKoNu, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitChuKoNu (const location_type& l)
      {
        return symbol_type (token::UnitChuKoNu, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitConquistador (location_type l)
      {
        return symbol_type (token::UnitConquistador, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitConquistador (const location_type& l)
      {
        return symbol_type (token::UnitConquistador, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteBerserk (location_type l)
      {
        return symbol_type (token::UnitEliteBerserk, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteBerserk (const location_type& l)
      {
        return symbol_type (token::UnitEliteBerserk, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteCataphract (location_type l)
      {
        return symbol_type (token::UnitEliteCataphract, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteCataphract (const location_type& l)
      {
        return symbol_type (token::UnitEliteCataphract, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteChuKoNu (location_type l)
      {
        return symbol_type (token::UnitEliteChuKoNu, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteChuKoNu (const location_type& l)
      {
        return symbol_type (token::UnitEliteChuKoNu, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteConquistador (location_type l)
      {
        return symbol_type (token::UnitEliteConquistador, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteConquistador (const location_type& l)
      {
        return symbol_type (token::UnitEliteConquistador, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteHuskarl (location_type l)
      {
        return symbol_type (token::UnitEliteHuskarl, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteHuskarl (const location_type& l)
      {
        return symbol_type (token::UnitEliteHuskarl, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteJaguarWarrior (location_type l)
      {
        return symbol_type (token::UnitEliteJaguarWarrior, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteJaguarWarrior (const location_type& l)
      {
        return symbol_type (token::UnitEliteJaguarWarrior, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteJanissary (location_type l)
      {
        return symbol_type (token::UnitEliteJanissary, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteJanissary (const location_type& l)
      {
        return symbol_type (token::UnitEliteJanissary, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteLongbowman (location_type l)
      {
        return symbol_type (token::UnitEliteLongbowman, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteLongbowman (const location_type& l)
      {
        return symbol_type (token::UnitEliteLongbowman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteMameluke (location_type l)
      {
        return symbol_type (token::UnitEliteMameluke, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteMameluke (const location_type& l)
      {
        return symbol_type (token::UnitEliteMameluke, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteMangudai (location_type l)
      {
        return symbol_type (token::UnitEliteMangudai, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteMangudai (const location_type& l)
      {
        return symbol_type (token::UnitEliteMangudai, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitElitePlumedArcher (location_type l)
      {
        return symbol_type (token::UnitElitePlumedArcher, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitElitePlumedArcher (const location_type& l)
      {
        return symbol_type (token::UnitElitePlumedArcher, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteSamurai (location_type l)
      {
        return symbol_type (token::UnitEliteSamurai, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteSamurai (const location_type& l)
      {
        return symbol_type (token::UnitEliteSamurai, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteTarkan (location_type l)
      {
        return symbol_type (token::UnitEliteTarkan, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteTarkan (const location_type& l)
      {
        return symbol_type (token::UnitEliteTarkan, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteTeutonicKnight (location_type l)
      {
        return symbol_type (token::UnitEliteTeutonicKnight, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteTeutonicKnight (const location_type& l)
      {
        return symbol_type (token::UnitEliteTeutonicKnight, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteThrowingAxeman (location_type l)
      {
        return symbol_type (token::UnitEliteThrowingAxeman, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteThrowingAxeman (const location_type& l)
      {
        return symbol_type (token::UnitEliteThrowingAxeman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteWarElephant (location_type l)
      {
        return symbol_type (token::UnitEliteWarElephant, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteWarElephant (const location_type& l)
      {
        return symbol_type (token::UnitEliteWarElephant, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteWarWagon (location_type l)
      {
        return symbol_type (token::UnitEliteWarWagon, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteWarWagon (const location_type& l)
      {
        return symbol_type (token::UnitEliteWarWagon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteWoadRaider (location_type l)
      {
        return symbol_type (token::UnitEliteWoadRaider, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteWoadRaider (const location_type& l)
      {
        return symbol_type (token::UnitEliteWoadRaider, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitHuskarl (location_type l)
      {
        return symbol_type (token::UnitHuskarl, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitHuskarl (const location_type& l)
      {
        return symbol_type (token::UnitHuskarl, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitJaguarWarrior (location_type l)
      {
        return symbol_type (token::UnitJaguarWarrior, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitJaguarWarrior (const location_type& l)
      {
        return symbol_type (token::UnitJaguarWarrior, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitJanissary (location_type l)
      {
        return symbol_type (token::UnitJanissary, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitJanissary (const location_type& l)
      {
        return symbol_type (token::UnitJanissary, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitLongbowman (location_type l)
      {
        return symbol_type (token::UnitLongbowman, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitLongbowman (const location_type& l)
      {
        return symbol_type (token::UnitLongbowman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMameluke (location_type l)
      {
        return symbol_type (token::UnitMameluke, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMameluke (const location_type& l)
      {
        return symbol_type (token::UnitMameluke, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMangudai (location_type l)
      {
        return symbol_type (token::UnitMangudai, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMangudai (const location_type& l)
      {
        return symbol_type (token::UnitMangudai, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitPetard (location_type l)
      {
        return symbol_type (token::UnitPetard, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitPetard (const location_type& l)
      {
        return symbol_type (token::UnitPetard, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitPlumedArcher (location_type l)
      {
        return symbol_type (token::UnitPlumedArcher, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitPlumedArcher (const location_type& l)
      {
        return symbol_type (token::UnitPlumedArcher, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitSamurai (location_type l)
      {
        return symbol_type (token::UnitSamurai, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitSamurai (const location_type& l)
      {
        return symbol_type (token::UnitSamurai, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTarkan (location_type l)
      {
        return symbol_type (token::UnitTarkan, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTarkan (const location_type& l)
      {
        return symbol_type (token::UnitTarkan, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTeutonicKnight (location_type l)
      {
        return symbol_type (token::UnitTeutonicKnight, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTeutonicKnight (const location_type& l)
      {
        return symbol_type (token::UnitTeutonicKnight, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitThrowingAxeman (location_type l)
      {
        return symbol_type (token::UnitThrowingAxeman, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitThrowingAxeman (const location_type& l)
      {
        return symbol_type (token::UnitThrowingAxeman, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTrebuchet (location_type l)
      {
        return symbol_type (token::UnitTrebuchet, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTrebuchet (const location_type& l)
      {
        return symbol_type (token::UnitTrebuchet, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitWarElephant (location_type l)
      {
        return symbol_type (token::UnitWarElephant, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitWarElephant (const location_type& l)
      {
        return symbol_type (token::UnitWarElephant, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitWarWagon (location_type l)
      {
        return symbol_type (token::UnitWarWagon, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitWarWagon (const location_type& l)
      {
        return symbol_type (token::UnitWarWagon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitWoadRaider (location_type l)
      {
        return symbol_type (token::UnitWoadRaider, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitWoadRaider (const location_type& l)
      {
        return symbol_type (token::UnitWoadRaider, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCannonGalleon (location_type l)
      {
        return symbol_type (token::UnitCannonGalleon, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCannonGalleon (const location_type& l)
      {
        return symbol_type (token::UnitCannonGalleon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitDemolitionShip (location_type l)
      {
        return symbol_type (token::UnitDemolitionShip, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitDemolitionShip (const location_type& l)
      {
        return symbol_type (token::UnitDemolitionShip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteCannonGalleon (location_type l)
      {
        return symbol_type (token::UnitEliteCannonGalleon, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteCannonGalleon (const location_type& l)
      {
        return symbol_type (token::UnitEliteCannonGalleon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteLongboat (location_type l)
      {
        return symbol_type (token::UnitEliteLongboat, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteLongboat (const location_type& l)
      {
        return symbol_type (token::UnitEliteLongboat, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEliteTurtleShip (location_type l)
      {
        return symbol_type (token::UnitEliteTurtleShip, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEliteTurtleShip (const location_type& l)
      {
        return symbol_type (token::UnitEliteTurtleShip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitFastFireShip (location_type l)
      {
        return symbol_type (token::UnitFastFireShip, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitFastFireShip (const location_type& l)
      {
        return symbol_type (token::UnitFastFireShip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitFireShip (location_type l)
      {
        return symbol_type (token::UnitFireShip, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitFireShip (const location_type& l)
      {
        return symbol_type (token::UnitFireShip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitFishingShip (location_type l)
      {
        return symbol_type (token::UnitFishingShip, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitFishingShip (const location_type& l)
      {
        return symbol_type (token::UnitFishingShip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitGalleon (location_type l)
      {
        return symbol_type (token::UnitGalleon, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitGalleon (const location_type& l)
      {
        return symbol_type (token::UnitGalleon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitGalley (location_type l)
      {
        return symbol_type (token::UnitGalley, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitGalley (const location_type& l)
      {
        return symbol_type (token::UnitGalley, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitHeavyDemolitionShip (location_type l)
      {
        return symbol_type (token::UnitHeavyDemolitionShip, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitHeavyDemolitionShip (const location_type& l)
      {
        return symbol_type (token::UnitHeavyDemolitionShip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitLongboat (location_type l)
      {
        return symbol_type (token::UnitLongboat, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitLongboat (const location_type& l)
      {
        return symbol_type (token::UnitLongboat, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTradeCog (location_type l)
      {
        return symbol_type (token::UnitTradeCog, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTradeCog (const location_type& l)
      {
        return symbol_type (token::UnitTradeCog, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTransportShip (location_type l)
      {
        return symbol_type (token::UnitTransportShip, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTransportShip (const location_type& l)
      {
        return symbol_type (token::UnitTransportShip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTurtleShip (location_type l)
      {
        return symbol_type (token::UnitTurtleShip, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTurtleShip (const location_type& l)
      {
        return symbol_type (token::UnitTurtleShip, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitWarGalley (location_type l)
      {
        return symbol_type (token::UnitWarGalley, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitWarGalley (const location_type& l)
      {
        return symbol_type (token::UnitWarGalley, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTradeCart (location_type l)
      {
        return symbol_type (token::UnitTradeCart, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTradeCart (const location_type& l)
      {
        return symbol_type (token::UnitTradeCart, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMissionary (location_type l)
      {
        return symbol_type (token::UnitMissionary, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMissionary (const location_type& l)
      {
        return symbol_type (token::UnitMissionary, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMonk (location_type l)
      {
        return symbol_type (token::UnitMonk, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMonk (const location_type& l)
      {
        return symbol_type (token::UnitMonk, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitBatteringRam (location_type l)
      {
        return symbol_type (token::UnitBatteringRam, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitBatteringRam (const location_type& l)
      {
        return symbol_type (token::UnitBatteringRam, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitBombardCannon (location_type l)
      {
        return symbol_type (token::UnitBombardCannon, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitBombardCannon (const location_type& l)
      {
        return symbol_type (token::UnitBombardCannon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCappedRam (location_type l)
      {
        return symbol_type (token::UnitCappedRam, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCappedRam (const location_type& l)
      {
        return symbol_type (token::UnitCappedRam, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitHeavyScorpion (location_type l)
      {
        return symbol_type (token::UnitHeavyScorpion, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitHeavyScorpion (const location_type& l)
      {
        return symbol_type (token::UnitHeavyScorpion, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMangonel (location_type l)
      {
        return symbol_type (token::UnitMangonel, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMangonel (const location_type& l)
      {
        return symbol_type (token::UnitMangonel, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitOnager (location_type l)
      {
        return symbol_type (token::UnitOnager, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitOnager (const location_type& l)
      {
        return symbol_type (token::UnitOnager, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitScorpion (location_type l)
      {
        return symbol_type (token::UnitScorpion, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitScorpion (const location_type& l)
      {
        return symbol_type (token::UnitScorpion, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitSiegeOnager (location_type l)
      {
        return symbol_type (token::UnitSiegeOnager, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitSiegeOnager (const location_type& l)
      {
        return symbol_type (token::UnitSiegeOnager, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitSiegeRam (location_type l)
      {
        return symbol_type (token::UnitSiegeRam, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitSiegeRam (const location_type& l)
      {
        return symbol_type (token::UnitSiegeRam, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCamel (location_type l)
      {
        return symbol_type (token::UnitCamel, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCamel (const location_type& l)
      {
        return symbol_type (token::UnitCamel, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCavalier (location_type l)
      {
        return symbol_type (token::UnitCavalier, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCavalier (const location_type& l)
      {
        return symbol_type (token::UnitCavalier, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitHeavyCamel (location_type l)
      {
        return symbol_type (token::UnitHeavyCamel, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitHeavyCamel (const location_type& l)
      {
        return symbol_type (token::UnitHeavyCamel, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitHussar (location_type l)
      {
        return symbol_type (token::UnitHussar, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitHussar (const location_type& l)
      {
        return symbol_type (token::UnitHussar, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitKnight (location_type l)
      {
        return symbol_type (token::UnitKnight, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitKnight (const location_type& l)
      {
        return symbol_type (token::UnitKnight, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitLightCavalry (location_type l)
      {
        return symbol_type (token::UnitLightCavalry, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitLightCavalry (const location_type& l)
      {
        return symbol_type (token::UnitLightCavalry, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitPaladin (location_type l)
      {
        return symbol_type (token::UnitPaladin, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitPaladin (const location_type& l)
      {
        return symbol_type (token::UnitPaladin, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitScoutCavalry (location_type l)
      {
        return symbol_type (token::UnitScoutCavalry, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitScoutCavalry (const location_type& l)
      {
        return symbol_type (token::UnitScoutCavalry, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitVillager (location_type l)
      {
        return symbol_type (token::UnitVillager, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitVillager (const location_type& l)
      {
        return symbol_type (token::UnitVillager, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitArcherLine (location_type l)
      {
        return symbol_type (token::UnitArcherLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitArcherLine (const location_type& l)
      {
        return symbol_type (token::UnitArcherLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCavalryArcherLine (location_type l)
      {
        return symbol_type (token::UnitCavalryArcherLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCavalryArcherLine (const location_type& l)
      {
        return symbol_type (token::UnitCavalryArcherLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitSkirmisherLine (location_type l)
      {
        return symbol_type (token::UnitSkirmisherLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitSkirmisherLine (const location_type& l)
      {
        return symbol_type (token::UnitSkirmisherLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitEagleWarriorLine (location_type l)
      {
        return symbol_type (token::UnitEagleWarriorLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitEagleWarriorLine (const location_type& l)
      {
        return symbol_type (token::UnitEagleWarriorLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMilitiamanLine (location_type l)
      {
        return symbol_type (token::UnitMilitiamanLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMilitiamanLine (const location_type& l)
      {
        return symbol_type (token::UnitMilitiamanLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitSpearmanLine (location_type l)
      {
        return symbol_type (token::UnitSpearmanLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitSpearmanLine (const location_type& l)
      {
        return symbol_type (token::UnitSpearmanLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitBerserkLine (location_type l)
      {
        return symbol_type (token::UnitBerserkLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitBerserkLine (const location_type& l)
      {
        return symbol_type (token::UnitBerserkLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCataphractLine (location_type l)
      {
        return symbol_type (token::UnitCataphractLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCataphractLine (const location_type& l)
      {
        return symbol_type (token::UnitCataphractLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitChuKoNuLine (location_type l)
      {
        return symbol_type (token::UnitChuKoNuLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitChuKoNuLine (const location_type& l)
      {
        return symbol_type (token::UnitChuKoNuLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitConquistadorLine (location_type l)
      {
        return symbol_type (token::UnitConquistadorLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitConquistadorLine (const location_type& l)
      {
        return symbol_type (token::UnitConquistadorLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitHuskarlLine (location_type l)
      {
        return symbol_type (token::UnitHuskarlLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitHuskarlLine (const location_type& l)
      {
        return symbol_type (token::UnitHuskarlLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitJaguarWarriorLine (location_type l)
      {
        return symbol_type (token::UnitJaguarWarriorLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitJaguarWarriorLine (const location_type& l)
      {
        return symbol_type (token::UnitJaguarWarriorLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitJanissaryLine (location_type l)
      {
        return symbol_type (token::UnitJanissaryLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitJanissaryLine (const location_type& l)
      {
        return symbol_type (token::UnitJanissaryLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitLongbowmanLine (location_type l)
      {
        return symbol_type (token::UnitLongbowmanLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitLongbowmanLine (const location_type& l)
      {
        return symbol_type (token::UnitLongbowmanLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMamelukeLine (location_type l)
      {
        return symbol_type (token::UnitMamelukeLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMamelukeLine (const location_type& l)
      {
        return symbol_type (token::UnitMamelukeLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMangudaiLine (location_type l)
      {
        return symbol_type (token::UnitMangudaiLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMangudaiLine (const location_type& l)
      {
        return symbol_type (token::UnitMangudaiLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitPlumedArcherLine (location_type l)
      {
        return symbol_type (token::UnitPlumedArcherLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitPlumedArcherLine (const location_type& l)
      {
        return symbol_type (token::UnitPlumedArcherLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitSamuraiLine (location_type l)
      {
        return symbol_type (token::UnitSamuraiLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitSamuraiLine (const location_type& l)
      {
        return symbol_type (token::UnitSamuraiLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTarkanLine (location_type l)
      {
        return symbol_type (token::UnitTarkanLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTarkanLine (const location_type& l)
      {
        return symbol_type (token::UnitTarkanLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTeutonicKnightLine (location_type l)
      {
        return symbol_type (token::UnitTeutonicKnightLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTeutonicKnightLine (const location_type& l)
      {
        return symbol_type (token::UnitTeutonicKnightLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitThrowingAxemanLine (location_type l)
      {
        return symbol_type (token::UnitThrowingAxemanLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitThrowingAxemanLine (const location_type& l)
      {
        return symbol_type (token::UnitThrowingAxemanLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitWarElephantLine (location_type l)
      {
        return symbol_type (token::UnitWarElephantLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitWarElephantLine (const location_type& l)
      {
        return symbol_type (token::UnitWarElephantLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitWarWagonLine (location_type l)
      {
        return symbol_type (token::UnitWarWagonLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitWarWagonLine (const location_type& l)
      {
        return symbol_type (token::UnitWarWagonLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitWoadRaiderLine (location_type l)
      {
        return symbol_type (token::UnitWoadRaiderLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitWoadRaiderLine (const location_type& l)
      {
        return symbol_type (token::UnitWoadRaiderLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCannonGalleonLine (location_type l)
      {
        return symbol_type (token::UnitCannonGalleonLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCannonGalleonLine (const location_type& l)
      {
        return symbol_type (token::UnitCannonGalleonLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitDemolitionShipLine (location_type l)
      {
        return symbol_type (token::UnitDemolitionShipLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitDemolitionShipLine (const location_type& l)
      {
        return symbol_type (token::UnitDemolitionShipLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitFireShipLine (location_type l)
      {
        return symbol_type (token::UnitFireShipLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitFireShipLine (const location_type& l)
      {
        return symbol_type (token::UnitFireShipLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitGalleyLine (location_type l)
      {
        return symbol_type (token::UnitGalleyLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitGalleyLine (const location_type& l)
      {
        return symbol_type (token::UnitGalleyLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitLongboatLine (location_type l)
      {
        return symbol_type (token::UnitLongboatLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitLongboatLine (const location_type& l)
      {
        return symbol_type (token::UnitLongboatLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTurtleShipLine (location_type l)
      {
        return symbol_type (token::UnitTurtleShipLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTurtleShipLine (const location_type& l)
      {
        return symbol_type (token::UnitTurtleShipLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitBatteringRamLine (location_type l)
      {
        return symbol_type (token::UnitBatteringRamLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitBatteringRamLine (const location_type& l)
      {
        return symbol_type (token::UnitBatteringRamLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMangonelLine (location_type l)
      {
        return symbol_type (token::UnitMangonelLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMangonelLine (const location_type& l)
      {
        return symbol_type (token::UnitMangonelLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitScorpionLine (location_type l)
      {
        return symbol_type (token::UnitScorpionLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitScorpionLine (const location_type& l)
      {
        return symbol_type (token::UnitScorpionLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCamelLine (location_type l)
      {
        return symbol_type (token::UnitCamelLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCamelLine (const location_type& l)
      {
        return symbol_type (token::UnitCamelLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitKnightLine (location_type l)
      {
        return symbol_type (token::UnitKnightLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitKnightLine (const location_type& l)
      {
        return symbol_type (token::UnitKnightLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitScoutCavalryLine (location_type l)
      {
        return symbol_type (token::UnitScoutCavalryLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitScoutCavalryLine (const location_type& l)
      {
        return symbol_type (token::UnitScoutCavalryLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMyEliteUniqueUnit (location_type l)
      {
        return symbol_type (token::UnitMyEliteUniqueUnit, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMyEliteUniqueUnit (const location_type& l)
      {
        return symbol_type (token::UnitMyEliteUniqueUnit, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMyUniqueUnit (location_type l)
      {
        return symbol_type (token::UnitMyUniqueUnit, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMyUniqueUnit (const location_type& l)
      {
        return symbol_type (token::UnitMyUniqueUnit, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitMyUniqueUnitLine (location_type l)
      {
        return symbol_type (token::UnitMyUniqueUnitLine, std::move (l));
      }
#else
      static
      symbol_type
      make_UnitMyUniqueUnitLine (const location_type& l)
      {
        return symbol_type (token::UnitMyUniqueUnitLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitAvailable (Fact v, location_type l)
      {
        return symbol_type (token::UnitAvailable, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UnitAvailable (const Fact& v, const location_type& l)
      {
        return symbol_type (token::UnitAvailable, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCount (Fact v, location_type l)
      {
        return symbol_type (token::UnitCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::UnitCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitCountTotal (Fact v, location_type l)
      {
        return symbol_type (token::UnitCountTotal, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UnitCountTotal (const Fact& v, const location_type& l)
      {
        return symbol_type (token::UnitCountTotal, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTypeCount (Fact v, location_type l)
      {
        return symbol_type (token::UnitTypeCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTypeCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::UnitTypeCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UnitTypeCountTotal (Fact v, location_type l)
      {
        return symbol_type (token::UnitTypeCountTotal, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UnitTypeCountTotal (const Fact& v, const location_type& l)
      {
        return symbol_type (token::UnitTypeCountTotal, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VictoryCondition (Fact v, location_type l)
      {
        return symbol_type (token::VictoryCondition, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_VictoryCondition (const Fact& v, const location_type& l)
      {
        return symbol_type (token::VictoryCondition, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VictoryConditionNameStandard (location_type l)
      {
        return symbol_type (token::VictoryConditionNameStandard, std::move (l));
      }
#else
      static
      symbol_type
      make_VictoryConditionNameStandard (const location_type& l)
      {
        return symbol_type (token::VictoryConditionNameStandard, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VictoryConditionNameConquest (location_type l)
      {
        return symbol_type (token::VictoryConditionNameConquest, std::move (l));
      }
#else
      static
      symbol_type
      make_VictoryConditionNameConquest (const location_type& l)
      {
        return symbol_type (token::VictoryConditionNameConquest, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VictoryConditionNameTimeLimit (location_type l)
      {
        return symbol_type (token::VictoryConditionNameTimeLimit, std::move (l));
      }
#else
      static
      symbol_type
      make_VictoryConditionNameTimeLimit (const location_type& l)
      {
        return symbol_type (token::VictoryConditionNameTimeLimit, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VictoryConditionNameScore (location_type l)
      {
        return symbol_type (token::VictoryConditionNameScore, std::move (l));
      }
#else
      static
      symbol_type
      make_VictoryConditionNameScore (const location_type& l)
      {
        return symbol_type (token::VictoryConditionNameScore, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VictoryConditionNameCustom (location_type l)
      {
        return symbol_type (token::VictoryConditionNameCustom, std::move (l));
      }
#else
      static
      symbol_type
      make_VictoryConditionNameCustom (const location_type& l)
      {
        return symbol_type (token::VictoryConditionNameCustom, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WallCompletedPercentage (Fact v, location_type l)
      {
        return symbol_type (token::WallCompletedPercentage, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WallCompletedPercentage (const Fact& v, const location_type& l)
      {
        return symbol_type (token::WallCompletedPercentage, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WallInvisiblePercentage (Fact v, location_type l)
      {
        return symbol_type (token::WallInvisiblePercentage, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WallInvisiblePercentage (const Fact& v, const location_type& l)
      {
        return symbol_type (token::WallInvisiblePercentage, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WallTypeFortifiedWall (location_type l)
      {
        return symbol_type (token::WallTypeFortifiedWall, std::move (l));
      }
#else
      static
      symbol_type
      make_WallTypeFortifiedWall (const location_type& l)
      {
        return symbol_type (token::WallTypeFortifiedWall, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WallTypePalisadeWall (location_type l)
      {
        return symbol_type (token::WallTypePalisadeWall, std::move (l));
      }
#else
      static
      symbol_type
      make_WallTypePalisadeWall (const location_type& l)
      {
        return symbol_type (token::WallTypePalisadeWall, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WallTypeStoneWall (location_type l)
      {
        return symbol_type (token::WallTypeStoneWall, std::move (l));
      }
#else
      static
      symbol_type
      make_WallTypeStoneWall (const location_type& l)
      {
        return symbol_type (token::WallTypeStoneWall, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WallTypeStoneWallLine (location_type l)
      {
        return symbol_type (token::WallTypeStoneWallLine, std::move (l));
      }
#else
      static
      symbol_type
      make_WallTypeStoneWallLine (const location_type& l)
      {
        return symbol_type (token::WallTypeStoneWallLine, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WarboatCount (Fact v, location_type l)
      {
        return symbol_type (token::WarboatCount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WarboatCount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::WarboatCount, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WoodAmount (Fact v, location_type l)
      {
        return symbol_type (token::WoodAmount, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WoodAmount (const Fact& v, const location_type& l)
      {
        return symbol_type (token::WoodAmount, v, l);
      }
#endif


  private:
    /// This class is not copyable.
    ScriptParser (const ScriptParser&);
    ScriptParser& operator= (const ScriptParser&);

    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    /// In theory \a t should be a token_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static token_number_type yytranslate_ (int t);

    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const short yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const short yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const short yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::reverse_iterator iterator;
      typedef typename S::const_reverse_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      std::ptrdiff_t
      ssize () const YY_NOEXCEPT
      {
        return std::ptrdiff_t (size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
      stack (const stack&);
      stack& operator= (const stack&);
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Some specific tokens.
    static const token_number_type yy_error_token_ = 1;
    static const token_number_type yy_undef_token_ = 2;

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 1560,     ///< Last index in yytable_.
      yynnts_ = 189,  ///< Number of nonterminal symbols.
      yyfinal_ = 6, ///< Termination state number.
      yyntokens_ = 673  ///< Number of tokens.
    };


    // User arguments.
    ai::ScriptLoader &driver;
    ai::ScriptTokenizer &scanner;
  };

  inline
  ScriptParser::token_number_type
  ScriptParser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   657,   658,   659,   660,   661,   662,   663,   664,
     665,   666,   667,   668,   669,   670,   671,   672
    };
    const int user_token_number_max_ = 927;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  ScriptParser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
    switch (this->type_get ())
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
        value.move< ActionType > (std::move (that.value));
        break;

      case 682: // age
        value.move< Age > (std::move (that.value));
        break;

      case 683: // building
        value.move< Building > (std::move (that.value));
        break;

      case 684: // civ
        value.move< Civ > (std::move (that.value));
        break;

      case 685: // commodity
        value.move< Commodity > (std::move (that.value));
        break;

      case 686: // difficultylevel
        value.move< DifficultyLevel > (std::move (that.value));
        break;

      case 687: // difficultyparameter
        value.move< DifficultyParameter > (std::move (that.value));
        break;

      case 688: // diplomaticstance
        value.move< DiplomaticStance > (std::move (that.value));
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
        value.move< Fact > (std::move (that.value));
        break;

      case 689: // mapsizetype
        value.move< MapSizeType > (std::move (that.value));
        break;

      case 690: // maptypename
        value.move< MapTypeName > (std::move (that.value));
        break;

      case 691: // playernumbertype
        value.move< PlayerNumberType > (std::move (that.value));
        break;

      case 692: // relop
        value.move< RelOp > (std::move (that.value));
        break;

      case 693: // researchitem
        value.move< ResearchItem > (std::move (that.value));
        break;

      case 694: // startingresourcestype
        value.move< StartingResourcesType > (std::move (that.value));
        break;

      case 695: // strategicnumbername
        value.move< StrategicNumberName > (std::move (that.value));
        break;

      case 696: // unit
        value.move< Unit > (std::move (that.value));
        break;

      case 697: // victoryconditionname
        value.move< VictoryConditionName > (std::move (that.value));
        break;

      case 698: // walltype
        value.move< WallType > (std::move (that.value));
        break;

      case 3: // Number
        value.move< int > (std::move (that.value));
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
        value.move< std::shared_ptr<ai::Action> > (std::move (that.value));
        break;

      case 676: // rule
        value.move< std::shared_ptr<ai::AiRule> > (std::move (that.value));
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
        value.move< std::shared_ptr<ai::Condition> > (std::move (that.value));
        break;

      case 4: // String
      case 5: // SymbolName
        value.move< std::string > (std::move (that.value));
        break;

      case 680: // actions
        value.move< std::vector<std::shared_ptr<ai::Action>> > (std::move (that.value));
        break;

      case 677: // conditions
        value.move< std::vector<std::shared_ptr<ai::Condition>> > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  ScriptParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->type_get ())
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
        value.copy< ActionType > (YY_MOVE (that.value));
        break;

      case 682: // age
        value.copy< Age > (YY_MOVE (that.value));
        break;

      case 683: // building
        value.copy< Building > (YY_MOVE (that.value));
        break;

      case 684: // civ
        value.copy< Civ > (YY_MOVE (that.value));
        break;

      case 685: // commodity
        value.copy< Commodity > (YY_MOVE (that.value));
        break;

      case 686: // difficultylevel
        value.copy< DifficultyLevel > (YY_MOVE (that.value));
        break;

      case 687: // difficultyparameter
        value.copy< DifficultyParameter > (YY_MOVE (that.value));
        break;

      case 688: // diplomaticstance
        value.copy< DiplomaticStance > (YY_MOVE (that.value));
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
        value.copy< Fact > (YY_MOVE (that.value));
        break;

      case 689: // mapsizetype
        value.copy< MapSizeType > (YY_MOVE (that.value));
        break;

      case 690: // maptypename
        value.copy< MapTypeName > (YY_MOVE (that.value));
        break;

      case 691: // playernumbertype
        value.copy< PlayerNumberType > (YY_MOVE (that.value));
        break;

      case 692: // relop
        value.copy< RelOp > (YY_MOVE (that.value));
        break;

      case 693: // researchitem
        value.copy< ResearchItem > (YY_MOVE (that.value));
        break;

      case 694: // startingresourcestype
        value.copy< StartingResourcesType > (YY_MOVE (that.value));
        break;

      case 695: // strategicnumbername
        value.copy< StrategicNumberName > (YY_MOVE (that.value));
        break;

      case 696: // unit
        value.copy< Unit > (YY_MOVE (that.value));
        break;

      case 697: // victoryconditionname
        value.copy< VictoryConditionName > (YY_MOVE (that.value));
        break;

      case 698: // walltype
        value.copy< WallType > (YY_MOVE (that.value));
        break;

      case 3: // Number
        value.copy< int > (YY_MOVE (that.value));
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
        value.copy< std::shared_ptr<ai::Action> > (YY_MOVE (that.value));
        break;

      case 676: // rule
        value.copy< std::shared_ptr<ai::AiRule> > (YY_MOVE (that.value));
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
        value.copy< std::shared_ptr<ai::Condition> > (YY_MOVE (that.value));
        break;

      case 4: // String
      case 5: // SymbolName
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case 680: // actions
        value.copy< std::vector<std::shared_ptr<ai::Action>> > (YY_MOVE (that.value));
        break;

      case 677: // conditions
        value.copy< std::vector<std::shared_ptr<ai::Condition>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  ScriptParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  ScriptParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
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
        value.move< ActionType > (YY_MOVE (s.value));
        break;

      case 682: // age
        value.move< Age > (YY_MOVE (s.value));
        break;

      case 683: // building
        value.move< Building > (YY_MOVE (s.value));
        break;

      case 684: // civ
        value.move< Civ > (YY_MOVE (s.value));
        break;

      case 685: // commodity
        value.move< Commodity > (YY_MOVE (s.value));
        break;

      case 686: // difficultylevel
        value.move< DifficultyLevel > (YY_MOVE (s.value));
        break;

      case 687: // difficultyparameter
        value.move< DifficultyParameter > (YY_MOVE (s.value));
        break;

      case 688: // diplomaticstance
        value.move< DiplomaticStance > (YY_MOVE (s.value));
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
        value.move< Fact > (YY_MOVE (s.value));
        break;

      case 689: // mapsizetype
        value.move< MapSizeType > (YY_MOVE (s.value));
        break;

      case 690: // maptypename
        value.move< MapTypeName > (YY_MOVE (s.value));
        break;

      case 691: // playernumbertype
        value.move< PlayerNumberType > (YY_MOVE (s.value));
        break;

      case 692: // relop
        value.move< RelOp > (YY_MOVE (s.value));
        break;

      case 693: // researchitem
        value.move< ResearchItem > (YY_MOVE (s.value));
        break;

      case 694: // startingresourcestype
        value.move< StartingResourcesType > (YY_MOVE (s.value));
        break;

      case 695: // strategicnumbername
        value.move< StrategicNumberName > (YY_MOVE (s.value));
        break;

      case 696: // unit
        value.move< Unit > (YY_MOVE (s.value));
        break;

      case 697: // victoryconditionname
        value.move< VictoryConditionName > (YY_MOVE (s.value));
        break;

      case 698: // walltype
        value.move< WallType > (YY_MOVE (s.value));
        break;

      case 3: // Number
        value.move< int > (YY_MOVE (s.value));
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
        value.move< std::shared_ptr<ai::Action> > (YY_MOVE (s.value));
        break;

      case 676: // rule
        value.move< std::shared_ptr<ai::AiRule> > (YY_MOVE (s.value));
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
        value.move< std::shared_ptr<ai::Condition> > (YY_MOVE (s.value));
        break;

      case 4: // String
      case 5: // SymbolName
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case 680: // actions
        value.move< std::vector<std::shared_ptr<ai::Action>> > (YY_MOVE (s.value));
        break;

      case 677: // conditions
        value.move< std::vector<std::shared_ptr<ai::Condition>> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  inline
  ScriptParser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  ScriptParser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  inline
  ScriptParser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  inline
  ScriptParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  ScriptParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  ScriptParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  ScriptParser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }

#line 9 "grammar.gen.ypp"
} //  ai 
#line 14424 "grammar.gen.tab.hpp"





#endif // !YY_YY_GRAMMAR_GEN_TAB_HPP_INCLUDED
