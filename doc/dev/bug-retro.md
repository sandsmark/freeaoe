Attempt at looking at issues that have appeared, some high-level analysis of
why and try to come up with solutions that would prevent it in the first place.


# Action buttons appeared in wrong position

`cada4078d6fdd6a322742c7fcb89f3ce46885276`

Reason: Stopped using int cast to fix clang-tidy warning, which was implicitly
used for floor()ing.

Solutions:
 - Don't do implicit flooring
 - Actually remove all integer divisions
    - Listen to clang-tidy

# Main menu selections didn't work

`bfa185a0b5a905d1b1d8af0111416d7e19fdef24`

Reason: Refactoring code with very complex flow without understanding why. Saw
clang-tidy react on single lines and thought I saw a generic problem.

Solutions: Actually clean up the mess in main(). Understand the flow of the
code before refactoring. Many levels of indentation -> code is harder to read
and indicates high cyclomatic complexity, so avoid it. The suggestions from
clang-tidy also worked improved the code in the end.

# Units could walk on water

`46b113f143a764e355b0b223239b22af3b08f20d`

Reason: Redid some pathfinding, unfortunately I didn't remember why I added 0.5
in the first place.

Solutions: Not sure. Don't redo too much at once, and test more while doing it?

# Stop button didn't work

`25a5a6259a52d7394b64b6b1ee7758fed929974c`

Reason: Didn't take queued actions into account.

Solutions: This was broken from the start, so more thorough manual testing.

# Terrain loading with HD assets stopped working

`9039a264900bacb23453a527e6c39b30be088408`

Reason: Merged in a lot of code without proper review and testing.

Solutions: More thorough reviewing of code that is merged, and test it beforehand.

# Mixed up unit IDs

`39cb281d48aac84fe66c22a5690588346379a801`

Reason: Changed to using unit IDs from unit data and not position in the vector
where they are stored in the dat file.

Solutions: Don't fix what isn't broken, verify new assumptions.
