package require Tk

option add *tearOff 0

#Sets the stats of the character
global stats
#Sets the inventory of the character
global inventory

#Sets all stats (stat1-stat5) as 5
set stats(stat1) 5
set stats(stat2) 5
set stats(stat3) 5
set stats(stat4) 5
set stats(stat5) 5

puts "[array exists stats]" ;#For debugging purposes. Will be commented out later.

#Creates the main window
wm title . "Recursion."
grid [ttk::frame .main -padding "10 10" -borderwidth 2] -column 0 -row 0 -sticky nwes
grid columnconfigure . 0 -weight 1; grid rowconfigure . 0 -weight 1

#Creates 3 canvasses that will serve 3 purposes.
#.main.stuff is the main window, it will show where the character is in the world and will be
# the main way through which the character interacts with the world.
#.main.wtree is the map of which world the character is in and which quests they need to complete.
#.main.local is a zoomed out map of the local area.
grid [tk::canvas .main.stuff -scrollregion "0 0 1000 1000"] -sticky nwes -column 0 -row 0 -columnspan 2 -rowspan 1
grid [tk::canvas .main.wtree -scrollregion "0 0 100 100"] -sticky nwes -column 4 -row 0
grid [tk::canvas .main.local -scrollregion "0 0 100 100"] -sticky nwes -column 4 -row 1

#Opens up numerous menus through which the player can adjust things such as their stats or what
#item to use from their inventory.
grid [ttk::button .main.b1 -text "Opt1" -command "CharWin"] -column 0 -row 2
grid [ttk::button .main.b2 -text "Opt2"] -column 1 -row 2
grid [ttk::button .main.b3 -text "Opt3"] -column 2 -row 2
grid [ttk::button .main.b4 -text "Opt4"] -column 3 -row 2
grid [ttk::button .main.b5 -text "Opt5"] -column 4 -row 2

#Creates the window through which the player can see their current character progression.
proc CharWin {} {
    puts "[array exists stats]" ;#For debugging purposes. Will be commented out later.

    #Creates the window
    toplevel .chr
    wm title .chr "Character."
    grid [ttk::frame .chr.cfr -padding "10 10" -borderwidth 2] -column 0 -row 0 -sticky nwes
    
    #These are the fixed labels.
    grid [ttk::label .chr.cfr.tex1 -text {Level:}] -column 0 -row 0
    grid [ttk::label .chr.cfr.tex2 -text {Current EXP:}] -column 0 -row 1
    grid [ttk::label .chr.cfr.tex3 -text {Next Level:}] -column 0 -row 2
    grid [ttk::label .chr.cfr.tex4 -text {Stat 1:}] -column 0 -row 4
    grid [ttk::label .chr.cfr.tex5 -text {Stat 2:}] -column 0 -row 5
    grid [ttk::label .chr.cfr.tex6 -text {Stat 3:}] -column 0 -row 6
    grid [ttk::label .chr.cfr.tex7 -text {Stat 4:}] -column 0 -row 7
    grid [ttk::label .chr.cfr.tex8 -text {Stat 5:}] -column 0 -row 8
    grid [ttk::label .chr.cfr.tex9 -text {Points Remaining:}] -column 0 -row 9

    #These are in theory the labels which display varying values.
    #Despite the fact that it claims that the array doesn't exist here (it should), it does.
    grid [ttk::label .chr.cfr.tex10 -textvariable Level] -column 1 -row 0 -sticky e
    grid [ttk::label .chr.cfr.tex11 -textvariable CurEXP] -column 3 -row 1 -sticky e
    grid [ttk::label .chr.cfr.tex12 -textvariable UntilNext] -column 3 -row 2 -sticky e
    grid [ttk::label .chr.cfr.tex13 -textvariable stats(stat1)] -column 2 -row 4 -sticky e
    grid [ttk::label .chr.cfr.tex14 -textvariable stats(stat2)] -column 2 -row 5 -sticky e
    grid [ttk::label .chr.cfr.tex15 -textvariable stats(stat3)] -column 2 -row 6 -sticky e
    grid [ttk::label .chr.cfr.tex16 -textvariable stats(stat4)] -column 2 -row 7 -sticky e
    grid [ttk::label .chr.cfr.tex17 -textvariable stats(stat5)] -column 2 -row 8 -sticky e
    grid [ttk::label .chr.cfr.tex18 -textvariable ptRem] -column 3 -row 9 -sticky e

    #Buttons for increasing the stats as desired.
    grid [ttk::button .chr.cfr.inst1 -text "+" -command "incStats 1"] -column 3 -row 4
    grid [ttk::button .chr.cfr.inst2 -text "+" -command "incStats 2"] -column 3 -row 5
    grid [ttk::button .chr.cfr.inst3 -text "+" -command "incStats 3"] -column 3 -row 6
    grid [ttk::button .chr.cfr.inst4 -text "+" -command "incStats 4"] -column 3 -row 7
    grid [ttk::button .chr.cfr.inst5 -text "+" -command "incStats 5"] -column 3 -row 8
}

proc incStats {num} {
    #I can't figure out how to get it into stats() here, so I put in a temporary function in the meantime.
    if {$num == 1} {puts "Incremented stat1"}
    if {$num == 2} {puts "Incremented stat2"}
    if {$num == 3} {puts "Incremented stat3"}
    if {$num == 4} {puts "Incremented stat4"}
    if {$num == 5} {puts "Incremented stat5"}
}

