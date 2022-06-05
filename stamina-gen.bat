@call clean.bat
@call clean-res.bat
@call cxx17 stamina-gen.cpp

@if exist stamina-gen.exe call stamina-gen.exe ru < data\phrases.ru > data\heavy_text_ru.txt 2>stamina-gen.log
@if exist stamina-gen.exe call stamina-gen.exe    < data\phrases.en > data\heavy_text_en.txt 2>stamina-gen.log
