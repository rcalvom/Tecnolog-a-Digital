VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3e"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL XLXN_1
        SIGNAL Data(7:0)
        SIGNAL LA
        SIGNAL EA
        SIGNAL Clock
        SIGNAL A(7:0)
        SIGNAL XLXN_8
        PORT Input Data(7:0)
        PORT Input LA
        PORT Input EA
        PORT Input Clock
        PORT Output A(7:0)
        BEGIN BLOCKDEF gnd
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 64 -64 64 -96 
            LINE N 76 -48 52 -48 
            LINE N 68 -32 60 -32 
            LINE N 88 -64 40 -64 
            LINE N 64 -64 64 -80 
            LINE N 64 -128 64 -96 
        END BLOCKDEF
        BEGIN BLOCKDEF sr8cle
            TIMESTAMP 2000 1 1 10 10 10
            RECTANGLE N 64 -640 320 -64 
            LINE N 0 -512 64 -512 
            RECTANGLE N 0 -524 64 -500 
            LINE N 0 -576 64 -576 
            RECTANGLE N 320 -396 384 -372 
            LINE N 0 -320 64 -320 
            LINE N 0 -192 64 -192 
            LINE N 0 -128 64 -128 
            LINE N 0 -32 64 -32 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 384 -384 320 -384 
        END BLOCKDEF
        BEGIN BLOCK XLXI_2 gnd
            PIN G XLXN_1
        END BLOCK
        BEGIN BLOCK XLXI_3 sr8cle
            PIN C Clock
            PIN CE EA
            PIN CLR XLXN_8
            PIN D(7:0) Data(7:0)
            PIN L LA
            PIN SLI XLXN_1
            PIN Q(7:0) A(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_4 gnd
            PIN G XLXN_8
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        INSTANCE XLXI_2 1120 1152 R0
        BEGIN BRANCH XLXN_1
            WIRE 1184 1008 1504 1008
            WIRE 1184 1008 1184 1024
        END BRANCH
        BEGIN BRANCH Data(7:0)
            WIRE 1472 1072 1504 1072
        END BRANCH
        IOMARKER 1472 1072 Data(7:0) R180 28
        BEGIN BRANCH LA
            WIRE 1472 1264 1504 1264
        END BRANCH
        IOMARKER 1472 1264 LA R180 28
        BEGIN BRANCH EA
            WIRE 1472 1392 1504 1392
        END BRANCH
        IOMARKER 1472 1392 EA R180 28
        BEGIN BRANCH Clock
            WIRE 1472 1456 1504 1456
        END BRANCH
        IOMARKER 1472 1456 Clock R180 28
        INSTANCE XLXI_3 1504 1584 R0
        BEGIN BRANCH A(7:0)
            WIRE 1888 1200 1920 1200
        END BRANCH
        IOMARKER 1920 1200 A(7:0) R0 28
        INSTANCE XLXI_4 1312 1696 R0
        BEGIN BRANCH XLXN_8
            WIRE 1376 1552 1504 1552
            WIRE 1376 1552 1376 1568
        END BRANCH
    END SHEET
END SCHEMATIC
