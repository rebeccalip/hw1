    COMP_FLAG = -std=c99 -Wall -Werror -pedantic-errors -DNDEBUG
    F_FOR_COMP = -I/home/mtm/public/2122b/ex1 -Itool
    DEBUG_FLAG = -g
	
    AsciiArtTool : RLEList.o tool/AsciiArtTool.o tool/main.o
	gcc $(COMP_FLAG) $(F_FOR_COMP) RLEList.o tool/AsciiArtTool.o tool/main.o -o AsciiArtTool
    RLEList.o : RLEList.c RLEList.h
	gcc $(COMP_FLAG) $(F_FOR_COMP) -c  RLEList.c 
    AsciiArtTool.o : RLEList.h tool/AsciiArtTool.c tool/AsciiArtTool.h
	gcc $(COMP_FLAG) $(F_FOR_COMP) -c tool/AsciiArtTool.c 
    main.o : tool/main.c tool/AsciiArtTool.h
	gcc $(COMP_FLAG) $(F_FOR_COMP) -c tool/main.c
    clean:
	rm -f RLEList.o tool/AsciiArtTool.o tool/main.o AsciiArtTool