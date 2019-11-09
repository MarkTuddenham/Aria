# DarkChess

Chess with fog of war.

[Wikipedia](https://en.wikipedia.org/wiki/Dark_chess)

---

## Build Process

```bash
mkdir -p _build/
cmake -H. -B_build/
# The above line may not work, if it doesn't then use:
# pushd _build/ && cmake .. && popd
cmake --build _build/

# Run an example
./bin/DarkChessExample
```
