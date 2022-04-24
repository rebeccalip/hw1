    CC = gcc
    RLEList = /home/mtm/public/2122b/ex1/RLEList
    MAIN = tool/main
    ASCII_ART_TOOL = tool/AsciiArtTool
    OBJS = $(ASCII_ART_TOOL).o RLEList.o $(MAIN).o
    EXEC = AsciiArtTool
    COMP_FLAG = -std=c99 -Wall -Werror -pedantic-errors -DNDEBUG -I/home/mtm/public/2122b/ex1 
    DEBUG_FLAG = -g

    $(EXEC) : $(OBJS)
	    $(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(OBJS) -o $@
    RLEList.o : RLEList.c $(RLEList).h
	    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG)  $*.c
    $(ASCII_ART_TOOL).o : tool/AsciiArtTool.h $(ASCII_ART_TOOL).c RLEList.c $(RLEList).h
	    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG)  $*.c -o $(ASCII_ART_TOOL).o
    $(MAIN).o : $(MAIN).c $(ASCII_ART_TOOL).h $(ASCII_ART_TOOL).c RLEList.c $(RLEList).h
	    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG)  $*.c -o $(MAIN).o

    clean :
	    rm -f $(OBJS) $(EXEC)