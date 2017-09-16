# Pokémon Gen 3 Uploader
A Wii homebrew app that reads data from a third generation handheld Pokémon game (Ruby, Sapphire, Emerald, FireRed, LeafGreen), and uploads it to a website for viewing. It does this by sending a multiboot binary to the GBA using the different multiboot protocol researched by Wack0 (whose repository this is forked from).

This came about when I wanted a way to show off the Pokémon I've raised on my website. I could have just used a tool to dump the save file and then written a script to extract data from it, but I wanted to do something more complicated, and came across the research done by Wack0. Thus I was able to turn this project into a great learning/research experience.

The multiboot image that the Wii sends to the GBA is executed in the context of the game, and thus is easily able to access its save data. It serializes data about the Pokémon in the save file, and sends them over the GCN-GBA link cable to the Wii. The Wii then further sanitizes the data, and then sends it over the network to a website.

One of the main reasons that I chose to use this method to extract save data from my GBA games is that I'm very concerned about the "legitimacy" of my Pokémon experience. I don't want to be able to do anything with my saves that could be considered cheating. Thus, the multiboot image only sends to the Wii information that is publicly visible using the game's interface. For instance, the Wii never receives a Pokémon's IVs, EVs, or full personality value. The GBA multiboot image derives all the necessary information (stats, Nature, gender, shininess, Unown letter, etc) from those values, and then sends that over the connection. In this way, this private information never leaves the context of the GBA's code.

This project is still in active development, and is not yet ready to be used.

# Compiling
`gen3uploader` depends on wolfSSL in order to negotiate HTTPS connections. The main branch has a couple of minor problems that prevent it from working with this project right out of the box, so for now you should use the [devkitpro branch in hatkirby/wolfssl](/hatkirby/wolfssl/tree/devkitpro).

In order to compile wolfSSL, first ensure your $DEVKITPPC environment variable is set. Then, assuming that $GEN3UPLOADER points to your `gen3uploader` repository, you can run the following commands:

```bash
./autogen.sh
./configure --disable-shared CC=$DEVKITPPC/bin/powerpc-eabi-gcc --host=ppc --enable-singlethreaded RANLIB=$DEVKITPPC/bin/powerpc-eabi-gcc-ranlib CFLAGS="-DDEVKITPRO -DNO_WRITEV" --disable-examples --disable-crypttests
make
cp src/.libs/libwolfssl.a $GEN3UPLOADER/vendor/lib/
cp -r wolfssl $GEN3UPLOADER/vendor/include/
```

From there, you should be able to run the `build.sh` script in the `gen3uploader` project to compile everything.

# Usage
Have a GC Controller in Port 1 and a GBA with Gen3 game in Port 2. Run the Wii program, and follow the instructions. The connection is not very stable, and it can take several tries for the program to run successfully.

# Acknowledgements
Thanks to FIX94 for your multiboot game dumper, which the multiboot code is loosely based on (differences in crypto & protocol...). Thanks to Wack0 for reverse-engineering the gen 3 "different" multiboot protocol.
