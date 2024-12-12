# SeisTrace
Seismic Trace library. Needed for SeisSegy.

# Build

git clone --recurse-submodules https://github.com/andalevor/SeisTrace.git

cd SeisTrace

meson setup -Dbuildtype=release build

meson compile -C build

meson install -C build
