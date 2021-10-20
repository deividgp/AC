sim-outorder -redir:sim applu.txt -config config.txt ../applu/exe/applu.exe < ../applu/data/ref/applu.in
sim-outorder -redir:sim crafty.txt -config config.txt ../crafty/exe/crafty.exe < ../crafty/data/ref/crafty.in
sim-outorder -redir:sim mesa.txt -config config.txt ../mesa/exe/mesa.exe -frames 1000 -meshfile ../mesa/data/ref/mesa.in -ppmfile mesa.ppm
sim-outorder -redir:sim vpr.txt -config config.txt ../vpr/exe/vpr.exe ../vpr/data/ref/net.in ../vpr/data/ref/arch.in ../vpr/data/ref/place.out ../vpr/data/ref/dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2 > place_log.out 2> place_log.err
#sim-outorder -redir:sim vortex.txt -config config.txt ../vortex/exe/vortex.exe ../vortex/data/ref/lendian1.raw > vortex1.out2 2> vortex1.err