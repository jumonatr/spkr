### WIN32 GENERATION INSTRUCTIONS ###

In the visual studio "Developer Command Prompt"

dumpbin /exports libvlc.dll > libvlc.def
// format the file to keep the function names and the string "EXPORTS" at the top

lib /def:libvlc.def /out:libvlc.lib