Here's my crack at learning embedded development whilst enjoying one of the finer things in life, the Gameboy Advanced (GBA)!

This ROM is still in development.

See `/documentation` for setup instructions on Windows 11 with WSL. This is a living document and may be out of date at the time you're reading it. I still have more to add myself

If you have any questions or need any advice, feel free to reach out.

NOTES:
* I have Run bound to `ctrl+f5` and Debug bound to `f5`. `/documentation/README.md` explains all of this.
    * Run/Debug use the emulator mgba-qt installed inside WSL using `apt install mgba-qt`
* There are two branches of code here:
    * You will see commits in both places mentioned below as I work through examples, refactor sections for readability, etc
    * All code in `./filbert` is written/copied&pasted by _me_ for _my_ GBA ROM creation
    * All code in `./tonc` is the example code & libraries that _Jasper Vijn_ provides for _their_ [GBA development tutorial](http://coranac.com/tonc/text/toc.htm)
        * Some of these ROMs won't compile through gcc's ARM compiler without first defining `__ctype_ptr__` in that ROM's code. See this [example](https://github.com/abullard/gba_study/blob/main/tonc/code/ext/bld_demo/bld_demo.c#L15-L16)
        * This code is much too valuable to not commit. There are workable/running examples for all major hardware concepts on the GBA
* I've included the GRIT (GBA Raster Image Transmogrifier) executable so that it's all bundled up in this repository
    * our .png and .bmps are converted to assembly files, and then stashed into a library, `libgfx.a`, to be linked to our ROM. See `gfxmake` file for more info
    * See GRIT's documentation for more info on this tool
        * [Manual](https://www.coranac.com/man/grit/html/grit.htm)
        * [GRIT in project builds](https://www.coranac.com/man/grit/html/gritmake.htm)
* The `/documentation` folder has some saved documents from [gbadev.org](https://gbadev.org/docs.php) outlining various toolchains and best practices