Attempt at looking at issues that have appeared, some high-level analysis of
why and try to come up with solutions that would prevent it in the first place.


# Action buttons appeared in wrong position

cada4078d6fdd6a322742c7fcb89f3ce46885276

Reason: Stopped using int cast to fix clang-tidy warning, which was implicitly
used for floor()ing.

Solutions:
 - Don't do implicit flooring
 - Actually remove all integer divisions
    - Listen to clang-tidy
