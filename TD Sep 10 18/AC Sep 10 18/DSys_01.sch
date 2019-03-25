VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3e"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        BEGIN BLOCKDEF dp_01
            TIMESTAMP 2018 9 10 13 31 23
            RECTANGLE N 64 -384 320 0 
            RECTANGLE N 0 -364 64 -340 
            LINE N 64 -352 0 -352 
            LINE N 64 -288 0 -288 
            LINE N 64 -224 0 -224 
            LINE N 64 -160 0 -160 
            LINE N 64 -96 0 -96 
            LINE N 64 -32 0 -32 
            RECTANGLE N 320 -364 384 -340 
            LINE N 320 -352 384 -352 
            LINE N 320 -192 384 -192 
            LINE N 320 -32 384 -32 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 dp_01
            PIN Data(7:0)
            PIN LA
            PIN EA
            PIN Clock
            PIN EB
            PIN LB
            PIN B(3:0)
            PIN z
            PIN a0
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        BEGIN INSTANCE XLXI_1 1856 1472 R0
        END INSTANCE
    END SHEET
END SCHEMATIC
