# Swiss Ephemeris Bindings

This repository contains C++ bindings for the ![Swiss Ephemeris](https://www.astro.com/swisseph/swephinfo_e.htm), a high precision ephemeris based upon the DExxx ephemerides from ![NASA's JPL](https://ssd.jpl.nasa.gov/orbits.html).


## Installation

In order to run this code, the ![Swiss Ephemeris code](https://github.com/aloistr/swisseph) must first be obtained and placed in `src/ephm` with the corresponding ![ephemeride files](https://github.com/aloistr/swisseph/tree/master/ephe) in `src/ephm/ephe`. Please visit ![their website](https://www.astro.com/swisseph/sweph_e.htm) for more information.

### Build Requirements

The following instructions are for installing NodeJS and building the ephemeris-server addon on in Ubuntu 22.04:

First, install NVM:
```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.3/install.sh | bash
```

Then follow the instructions to update `~/.bashrc` by adding the following:
```bash
export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion
```

Reload `~/.bashrc` and verify the nvm installation:
```bash
source ~/.bashrc
nvm --version
```

This should return `0.39.3`, after which the latest NodeJS may be installed (at the time of writing, latest is v20.9.0):
```bash
nvm install --lts
```

Next, install the necessary C++ libraries first by installing the `build-essential` package to get the GCC make tools:
```bash
sudo apt-get install build-essential
```

Then create a `lib` directory and download and unpack the ![Boost library](https://www.boost.org/doc/libs/1_83_0/more/getting_started/unix-variants.html) into that folder:
```bash
mkdir ./lib && cd lib
wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.bz2
tar --bzip2 -xf boost_1_82_0.tar.bz2
```

Finally, update the paths of `binding.gyp` to ensure the correct base path is given, then install the node package:
```bash
npm install
```

Verify the installation was successful:
```bash
node test.js
```

You should see the following information printed to terminal (console output):
```
date: 01 January 2023 at 0:00 Universal time, jd=2459945.5
planet          longitude       latitude        distance        speed long.
       Sun      280.2838870     -0.0000616       0.9833367       1.0190288
      Moon       33.6479912     -0.7212078       0.0026042      12.7204013
   Mercury      293.7019368      0.8658190       0.7491323      -0.5080338
     Venus      297.3826285     -1.3812102       1.6075162       1.2525753
      Mars       69.0657735      2.8138554       0.6384187      -0.1597034
   Jupiter        1.1929697     -1.2868636       5.0103898       0.1206121
    Saturn      322.4188522     -1.2434139      10.5424836       0.0997630
    Uranus       45.1476005     -0.3568837      19.0913848      -0.0185023
   Neptune      352.8706151     -1.1867884      30.1920990       0.0159213
     Pluto      297.6578268     -2.2520770      35.6138296       0.0315590
 mean Node       40.2035723      0.0000000       0.0025696      -0.0529535
 true Node       41.7529580      0.0000000       0.0026228       0.0115354
mean Apogee     119.1516781      5.0504678       0.0027106       0.1120195
osc. Apogee      97.2308406      4.2072760       0.0026919       2.3857261
    Chiron       11.9690465      1.7650291      18.7595102       0.0079181
01.01.2023
```