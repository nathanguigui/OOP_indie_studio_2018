Outfile "BombermanInstaller.exe"

InstallDir $DESKTOP\Bomberman

Section Lib
SetOutPath $INSTDIR
File "*.dll"
File "*.lib"
File "*.pdb"
SectionEnd

Section Media
SetOutPath $INSTDIR\media
File /nonfatal /a /r "media\"
SectionEnd

Section Bin
SetOutPath $INSTDIR\bin
File /nonfatal /a /r "bin\"
SectionEnd