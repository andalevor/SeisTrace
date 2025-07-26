# SeisTrace
Seismic Trace library. Needed for SeisSegy.

# Build

1) git clone --recurse-submodules https://github.com/andalevor/SeisTrace.git

2) cd SeisTrace

3) meson setup -Dbuildtype=release -Db_ndebug=true build

4) meson compile -C build seistrace

5) meson install -C build
