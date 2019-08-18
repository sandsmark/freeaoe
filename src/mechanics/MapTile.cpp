#include "MapTile.h"
#include "resource/Terrain.h"

MapTile MapTile::null;

std::vector<genie::Pattern> MapTile::slopePatterns() const noexcept
{
    // The correct patterns for the different slopes is from aoetwols by aap
    // (I just chose a much more horrible way of looking up and storing them, FIXME I guess)
    std::vector<genie::Pattern> patterns;
    switch (slopes.self) {
    case Slope::SouthUp: {
        patterns.push_back(genie::DiagDownPattern);

        if (slopes.south == Slope::Flat) {
            patterns.push_back(genie::Pattern18);
        }

        if ((slopes.northWest == Slope::Flat) + (slopes.north == Slope::Flat) + (slopes.northEast == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern19);
        }

        if (slopes.northWest == Slope::Flat || slopes.northWest == Slope::NorthUp || slopes.northWest == Slope::WestUp || slopes.northWest == Slope::NorthWestUp) {
            patterns.push_back(genie::DownPattern);
        } else if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopes.northEast != Slope::Flat && slopes.northEast != Slope::NorthUp && slopes.northEast != Slope::EastUp && slopes.northEast != Slope::NorthEastUp) {
            if (slopes.east != Slope::Flat) {
                patterns.push_back(genie::Pattern28);
            }
        } else {
            patterns.push_back(genie::HalfRightPattern);
        }

        if (slopes.northEast == Slope::SouthWestEastUp || slopes.southEast == Slope::SouthWestEastUp || slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern22);
        }
        if (slopes.northWest == Slope::SouthWestEastUp || slopes.southWest == Slope::SouthWestEastUp || slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern21);
        }

        break;
    }
    case Slope::NorthUp: {
        patterns.push_back(genie::DiagDownPattern);
        if (slopes.north == Slope::Flat) {
            patterns.push_back(genie::Pattern16);
        }
        if ((slopes.southWest == Slope::Flat) + (slopes.south == Slope::Flat) + (slopes.southEast == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern17);
        }

        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::SouthUp || slopes.northWest == Slope::WestUp || slopes.southWest == Slope::SouthWestUp) {
            patterns.push_back(genie::LeftPattern);
        } else if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopes.southEast != Slope::Flat && slopes.southEast != Slope::SouthUp && slopes.southEast != Slope::EastUp && slopes.southEast != Slope::SouthEastUp) {
            if (slopes.east != Slope::Flat) {
                patterns.push_back(genie::Pattern28);
            }
        } else {
            patterns.push_back(genie::HalfUpPattern);
        }
        if (slopes.northWest == Slope::NorthWestEastUp || slopes.southWest == Slope::NorthWestEastUp || slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern21);
        }

        if (slopes.northEast == Slope::NorthWestEastUp || slopes.southEast == Slope::NorthWestEastUp || slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern22);
        }

        break;
    }
    case Slope::WestUp: {
        patterns.push_back(genie::FlatPattern);
        if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern12);
        }

        if ((slopes.northEast == Slope::Flat) + (slopes.east == Slope::Flat) + (slopes.southEast == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern13);
        }

        if (slopes.northEast == Slope::Flat || slopes.northEast == Slope::NorthUp || slopes.northEast == Slope::EastUp || slopes.southWest == Slope::NorthEastUp) {
            patterns.push_back(genie::HalfRightPattern);
        } else if (slopes.north == Slope::Flat) {
            patterns.push_back(genie::Pattern34);
        }

        if (!(slopes.southEast == Slope::Flat || slopes.southEast == Slope::SouthUp || slopes.northEast == Slope::EastUp || slopes.northEast == Slope::SouthEastUp)) {
            if (slopes.south != Slope::Flat) {
                patterns.push_back(genie::Pattern35);
            }
        } else {
            patterns.push_back(genie::HalfUpPattern);
        }

        break;
    }
    case Slope::EastUp: {
        patterns.push_back(genie::BlackPattern);

        if (slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern14);
        }

        if ((slopes.northWest == Slope::Flat) + (slopes.west == Slope::Flat) + (slopes.southWest == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern15);
        }

        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::SouthUp || slopes.southWest == Slope::WestUp || slopes.southWest == Slope::SouthWestUp) {
            patterns.push_back(genie::LeftPattern);
        } else if (slopes.south == Slope::Flat) {
            patterns.push_back(genie::Pattern37);
        }

        if (slopes.northWest != Slope::Flat && slopes.northWest != Slope::NorthUp && slopes.northWest != Slope::WestUp && slopes.northWest != Slope::NorthWestUp) {
            if (slopes.north != Slope::Flat) {
                patterns.push_back(genie::Pattern36);
            }
        } else {
            patterns.push_back(genie::DownPattern);
        }

        break;
    }
    case Slope::SouthWestUp: {
        patterns.push_back(genie::FlatPattern);
        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::NorthEastUp || slopes.southWest == Slope::NorthSouthEastUp || slopes.southWest == Slope::NorthWestEastUp) {
            patterns.push_back(genie::HalfLeftPattern);
        } else {
            if (slopes.west == Slope::Flat) {
                patterns.push_back(genie::Pattern12);
            }

            if (slopes.south == Slope::Flat) {
                patterns.push_back(genie::Pattern35);
            }
        }

        if (slopes.northEast == Slope::Flat || slopes.northEast == Slope::NorthUp || slopes.northEast == Slope::EastUp || slopes.northEast == Slope::NorthEastUp) {
            patterns.push_back(genie::HalfRightPattern);
        } else {
            if (slopes.north == Slope::Flat || slopes.north == Slope::SouthUp) {
                patterns.push_back(genie::Pattern34);
            }
            if (slopes.east == Slope::Flat || slopes.east == Slope::EastUp) {
                patterns.push_back(genie::Pattern28);
            }
        }

        if (slopes.south == Slope::SouthUp && slopes.southWest == Slope::WestUp) {
            patterns.push_back(genie::Pattern35);
        }

        if (slopes.southWest == Slope::SouthUp && slopes.west == Slope::WestUp) {
            patterns.push_back(genie::Pattern12);
        }

        if (slopes.northEast == Slope::SouthWestEastUp || slopes.southEast == Slope::SouthWestEastUp) {
            patterns.push_back(genie::Pattern22);
        }

        if (slopes.northWest == Slope::SouthUp) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern28);
        }

        break;
    }
    case Slope::NorthWestUp: {
        patterns.push_back(genie::FlatPattern);
        if (slopes.northWest == Slope::Flat || slopes.northWest == Slope::SouthEastUp || slopes.northWest == Slope::NorthSouthEastUp || slopes.northWest == Slope::SouthWestEastUp) {
            patterns.push_back(genie::HalfDownPattern);
        } else {
            if (slopes.west == Slope::Flat) {
                patterns.push_back(genie::Pattern12);
            }
            if (slopes.north == Slope::Flat) {
                patterns.push_back(genie::Pattern34);
            }
        }

        if (slopes.southEast == Slope::Flat || slopes.southEast == Slope::SouthUp || slopes.southEast == Slope::EastUp || slopes.southEast == Slope::SouthEastUp) {
            patterns.push_back(genie::HalfUpPattern);
        } else {
            if (slopes.south == Slope::Flat || slopes.south == Slope::SouthUp) {
                patterns.push_back(genie::Pattern35);
            }

            if (slopes.east == Slope::Flat || slopes.east == Slope::EastUp) {
                patterns.push_back(genie::Pattern28);
            }
        }

        if (slopes.southWest == Slope::NorthUp) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern12);
        }

        if (slopes.northEast == Slope::NorthWestEastUp) {
            patterns.push_back(genie::Pattern22);
        }

        if (slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern28);
        }

        if (slopes.north == Slope::Flat) {
            patterns.push_back(genie::Pattern34);
        }

        if (slopes.west == Slope::WestUp && slopes.northWest == Slope::NorthUp) {
            patterns.push_back(genie::Pattern12);
        }

        if (slopes.northWest == Slope::WestUp && slopes.north == Slope::NorthUp) {
            patterns.push_back(genie::Pattern34);
        }

        break;
    }
    case Slope::SouthEastUp: {
        patterns.push_back(genie::BlackPattern);

        if (slopes.northWest == Slope::Flat || slopes.northWest == Slope::NorthUp || slopes.northWest == Slope::WestUp || slopes.northWest == Slope::NorthWestUp) {
            patterns.push_back(genie::DownPattern);
        } else if (slopes.west == Slope::Flat || slopes.west == Slope::WestUp) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopes.north == Slope::Flat || slopes.north == Slope::NorthUp) {
            patterns.push_back(genie::Pattern36);
        }

        if (slopes.southEast == Slope::Flat || slopes.southEast == Slope::NorthWestUp || slopes.southEast == Slope::NorthSouthWestUp || slopes.southEast == Slope::NorthWestEastUp) {
            patterns.push_back(genie::UpPattern);
        } else {
            if (slopes.east == Slope::Flat){
                patterns.push_back(genie::Pattern14);
            }
            if (slopes.south == Slope::Flat){
                patterns.push_back(genie::Pattern37);
            }
        }

        if (slopes.south == Slope::SouthUp && slopes.southEast == Slope::EastUp) {
            patterns.push_back(genie::Pattern37);
        }

        if (slopes.southEast == Slope::SouthUp && slopes.east == Slope::EastUp) {
            patterns.push_back(genie::Pattern14);
        }

        if (slopes.northEast == Slope::SouthUp) {
            patterns.push_back(genie::Pattern20);
        }

        if (slopes.west == Slope::SouthUp) {
            patterns.push_back(genie::Pattern21);
        }

        if (slopes.northWest == Slope::SouthWestEastUp) {
            patterns.push_back(genie::Pattern21);
        }

        break;
    }
    case Slope::NorthEastUp: {
        patterns.push_back(genie::BlackPattern);

        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::SouthWestUp || slopes.southWest == Slope::WestUp || slopes.southWest == Slope::SouthUp) {
            patterns.push_back(genie::LeftPattern);
        } else {
            if (slopes.west == Slope::Flat || slopes.west == Slope::WestUp) {
                patterns.push_back(genie::Pattern26);
            }
            if (slopes.south == Slope::Flat || slopes.south == Slope::SouthUp) {
                patterns.push_back(genie::Pattern37);
            }
        }

        if (slopes.northEast == Slope::Flat || slopes.northEast == Slope::SouthWestUp || slopes.northEast == Slope::SouthWestEastUp || slopes.northEast == Slope::NorthSouthWestUp) {
            patterns.push_back(genie::RightPattern);
        } else {
            if(slopes.north == Slope::Flat) {
                patterns.push_back(genie::Pattern36);
            }
            if (slopes.east == Slope::Flat) {
                patterns.push_back(genie::Pattern14);
            }
        }

        if (slopes.east == Slope::EastUp || slopes.northEast == Slope::NorthUp) {
            patterns.push_back(genie::Pattern14);
        }

        if (slopes.northEast == Slope::EastUp || slopes.north == Slope::NorthUp) {
            patterns.push_back(genie::Pattern36);
        }

        if (slopes.southEast == Slope::NorthUp) {
            patterns.push_back(genie::Pattern20);
        }

        if (slopes.northWest == Slope::NorthWestEastUp) {
            patterns.push_back(genie::Pattern21);
        }
        if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern26);
        }

        break;
    }
    case Slope::SouthWestEastUp: {
        patterns.push_back(genie::DiagUpPattern);

        if (slopes.north == Slope::Flat) {
            patterns.push_back(genie::Pattern30);
        }

        if ((slopes.southEast == Slope::Flat) + (slopes.southWest == Slope::Flat) + (slopes.south == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern31);
        }

        if (slopes.southEast == Slope::Flat || slopes.southEast == Slope::NorthWestUp || slopes.southEast == Slope::NorthSouthWestUp || slopes.southEast == Slope::NorthWestEastUp) {
            patterns.push_back(genie::UpPattern);
        }

        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::NorthEastUp || slopes.southWest == Slope::NorthSouthEastUp || slopes.southWest == Slope::NorthWestEastUp) {
            patterns.push_back(genie::HalfLeftPattern);
        }

        if (slopes.south == Slope::SouthUp) {
            patterns.push_back(genie::Pattern22);
        }

        if (slopes.southWest == Slope::SouthUp) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopes.northWest == Slope::SouthUp) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopes.northEast == Slope::SouthUp) {
            patterns.push_back(genie::Pattern20);
        }

        if (slopes.southEast == Slope::SouthUp) {
            patterns.push_back(genie::Pattern20);
        }

        break;
    }
    case Slope::NorthSouthWestUp: {
        patterns.push_back(genie::FlatPattern);

        if (slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern28);
        }

        if ((slopes.northWest == Slope::Flat) + (slopes.southWest == Slope::Flat) + (slopes.west == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern29);
        }

        if (slopes.east == Slope::EastUp || slopes.east == Slope::NorthEastUp || slopes.east == Slope::SouthEastUp) {
            patterns.push_back(genie::Pattern28);
        }

        if (slopes.northWest == Slope::Flat || slopes.northWest == Slope::SouthEastUp || slopes.northWest == Slope::SouthWestEastUp || slopes.northWest == Slope::NorthSouthEastUp) {
            patterns.push_back(genie::HalfDownPattern);
        } else {
            if (slopes.north == Slope::Flat || slopes.north == Slope::NorthUp) {
                patterns.push_back(genie::Pattern34);
            }

            if (slopes.northWest == Slope::NorthUp) {
                patterns.push_back(genie::Pattern12);
            }
        }

        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::NorthEastUp || slopes.southWest == Slope::NorthWestEastUp || slopes.southWest == Slope::NorthSouthEastUp) {
            patterns.push_back(genie::HalfLeftPattern);
        } else {
            if (slopes.south == Slope::Flat) {
                patterns.push_back(genie::Pattern35);
            }

            if (slopes.southWest == Slope::SouthUp) {
                patterns.push_back(genie::Pattern12);
            }
        }

        if (slopes.northEast == Slope::NorthWestEastUp) {
            patterns.push_back(genie::Pattern22);
        }

        if (slopes.southEast == Slope::SouthWestEastUp) {
            patterns.push_back(genie::Pattern28);
        }

        break;
    }
    case Slope::NorthSouthEastUp: {
        patterns.push_back(genie::BlackPattern);

        if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern26);
        }

        if ((slopes.northEast == Slope::Flat) + (slopes.southEast == Slope::Flat) + (slopes.east == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern27);
        }

        if (slopes.west == Slope::WestUp || slopes.west == Slope::NorthWestUp || slopes.west == Slope::SouthWestUp) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopes.northEast == Slope::Flat || slopes.northEast == Slope::SouthWestUp || slopes.northEast == Slope::SouthWestEastUp || slopes.northEast == Slope::NorthSouthWestUp) {
            patterns.push_back(genie::RightPattern);
        } else {
            if (slopes.north == Slope::Flat) {
                patterns.push_back(genie::Pattern36);
            }
            if (slopes.northEast == Slope::NorthUp) {
                patterns.push_back(genie::Pattern14);
            }
        }

        if (slopes.southEast == Slope::Flat || slopes.southEast == Slope::NorthWestUp || slopes.southEast == Slope::NorthWestEastUp || slopes.southEast == Slope::NorthSouthWestUp) {
            patterns.push_back(genie::UpPattern);
        } else {
            if (slopes.south == Slope::Flat) {
                patterns.push_back(genie::Pattern37);
            }
            if (slopes.southEast == Slope::SouthUp) {
                patterns.push_back(genie::Pattern14);
            }
        }

        if (slopes.northWest == Slope::NorthWestEastUp) {
            patterns.push_back(genie::Pattern21);
        }
        if (slopes.southWest == Slope::SouthWestEastUp) {
            patterns.push_back(genie::Pattern26);
        }

        break;
    }
    case Slope::NorthWestEastUp: {
        patterns.push_back(genie::DiagUpPattern);

        if ((slopes.northEast == Slope::Flat) + (slopes.northWest == Slope::Flat) + (slopes.north == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern33);
        }

        if (slopes.south == Slope::Flat) {
            patterns.push_back(genie::Pattern32);
        }

        if (slopes.northWest == Slope::Flat || slopes.northWest == Slope::SouthEastUp || slopes.northWest == Slope::NorthSouthEastUp || slopes.northWest == Slope::SouthWestEastUp) {
            patterns.push_back(genie::HalfDownPattern);
        }
        if (slopes.northEast == Slope::Flat || slopes.northEast == Slope::SouthWestUp || slopes.northEast == Slope::NorthSouthWestUp || slopes.northEast == Slope::SouthWestEastUp) {
            patterns.push_back(genie::RightPattern);
        }

        if (slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern20);
        }

        if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopes.southWest == Slope::NorthUp) {
            patterns.push_back(genie::Pattern23);
        }
        if (slopes.northWest == Slope::NorthUp) {
            patterns.push_back(genie::Pattern23);
        }
        if (slopes.southEast == Slope::NorthUp) {
            patterns.push_back(genie::Pattern20);
        }
        if (slopes.northEast == Slope::NorthUp) {
            patterns.push_back(genie::Pattern20);
        }

        break;
    }

    default:
//        patterns.push_back(genie::BlackPattern);
//        WARN << "unhandled slope" << slopes.self.direction;
        break;
    }

    return patterns;

}
