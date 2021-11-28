#Applu
sim-outorder -redir:sim gshareApplu8 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 8 3 1 -mem:width 32 -mem:lat 300 2 ../../../applu/exe/applu.exe < ../../../applu/data/ref/applu.in
sim-outorder -redir:sim gshareApplu32 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 32 5 1 -mem:width 32 -mem:lat 300 2 ../../../applu/exe/applu.exe < ../../../applu/data/ref/applu.in
sim-outorder -redir:sim gshareApplu128 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 128 7 1 -mem:width 32 -mem:lat 300 2 ../../../applu/exe/applu.exe < ../../../applu/data/ref/applu.in
sim-outorder -redir:sim gshareApplu512 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 512 9 1 -mem:width 32 -mem:lat 300 2 ../../../applu/exe/applu.exe < ../../../applu/data/ref/applu.in
sim-outorder -redir:sim gshareApplu2048 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 2048 11 1 -mem:width 32 -mem:lat 300 2 ../../../applu/exe/applu.exe < ../../../applu/data/ref/applu.in
#Crafty
sim-outorder -redir:sim gshareCrafty8 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 8 3 1 -mem:width 32 -mem:lat 300 2 ../../../crafty/exe/crafty.exe < ../../../crafty/data/ref/crafty.in
sim-outorder -redir:sim gshareCrafty32 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 32 5 1 -mem:width 32 -mem:lat 300 2 ../../../crafty/exe/crafty.exe < ../../../crafty/data/ref/crafty.in
sim-outorder -redir:sim gshareCrafty128 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 128 7 1 -mem:width 32 -mem:lat 300 2 ../../../crafty/exe/crafty.exe < ../../../crafty/data/ref/crafty.in
sim-outorder -redir:sim gshareCrafty512 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 512 9 1 -mem:width 32 -mem:lat 300 2 ../../../crafty/exe/crafty.exe < ../../../crafty/data/ref/crafty.in
sim-outorder -redir:sim gshareCrafty2048 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 2048 11 1 -mem:width 32 -mem:lat 300 2 ../../../crafty/exe/crafty.exe < ../../../crafty/data/ref/crafty.in
#Mesa
sim-outorder -redir:sim gshareMesa8 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 8 3 1 -mem:width 32 -mem:lat 300 2 ../../../mesa/exe/mesa.exe -frames 1000 -meshfile ../../../mesa/data/ref/mesa.in -ppmfile ../../../mesa/data/ref/mesa.ppm
sim-outorder -redir:sim gshareMesa32 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 32 5 1 -mem:width 32 -mem:lat 300 2 ../../../mesa/exe/mesa.exe -frames 1000 -meshfile ../../../mesa/data/ref/mesa.in -ppmfile ../../../mesa/data/ref/mesa.ppm
sim-outorder -redir:sim gshareMesa128 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 128 7 1 -mem:width 32 -mem:lat 300 2 ../../../mesa/exe/mesa.exe -frames 1000 -meshfile ../../../mesa/data/ref/mesa.in -ppmfile ../../../mesa/data/ref/mesa.ppm
sim-outorder -redir:sim gshareMesa512 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 512 9 1 -mem:width 32 -mem:lat 300 2 ../../../mesa/exe/mesa.exe -frames 1000 -meshfile ../../../mesa/data/ref/mesa.in -ppmfile ../../../mesa/data/ref/mesa.ppm
sim-outorder -redir:sim gshareMesa2048 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 2048 11 1 -mem:width 32 -mem:lat 300 2 ../../../mesa/exe/mesa.exe -frames 1000 -meshfile ../../../mesa/data/ref/mesa.in -ppmfile ../../../mesa/data/ref/mesa.ppm
#Vpr
sim-outorder -redir:sim gshareVpr8 -fastfwd 50000000 -max:inst 65000000  -bpred 2lev -bpred:2lev 1 8 3 1 -mem:width 32 -mem:lat 300 2 ../../../vpr/exe/vpr.exe ../../../vpr/data/ref/net.in ../../../vpr/data/ref/arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2
sim-outorder -redir:sim gshareVpr32 -fastfwd 50000000 -max:inst 65000000  -bpred 2lev -bpred:2lev 1 32 5 1 -mem:width 32 -mem:lat 300 2 ../../../vpr/exe/vpr.exe ../../../vpr/data/ref/net.in ../../../vpr/data/ref/arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2
sim-outorder -redir:sim gshareVpr128 -fastfwd 50000000 -max:inst 65000000  -bpred 2lev -bpred:2lev 1 128 7 1 -mem:width 32 -mem:lat 300 2 ../../../vpr/exe/vpr.exe ../../../vpr/data/ref/net.in ../../../vpr/data/ref/arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2
sim-outorder -redir:sim gshareVpr512 -fastfwd 50000000 -max:inst 65000000  -bpred 2lev -bpred:2lev 1 512 9 1 -mem:width 32 -mem:lat 300 2 ../../../vpr/exe/vpr.exe ../../../vpr/data/ref/net.in ../../../vpr/data/ref/arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2
sim-outorder -redir:sim gshareVpr2048 -fastfwd 50000000 -max:inst 65000000  -bpred 2lev -bpred:2lev 1 2048 11 1 -mem:width 32 -mem:lat 300 2 ../../../vpr/exe/vpr.exe ../../../vpr/data/ref/net.in ../../../vpr/data/ref/arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2
#Vortex                                                                                           
sim-outorder -redir:sim gshareVortex8 -fastfwd 50000000 -max:inst 65000000 -bpred 2lev -bpred:2lev 1 8 3 1 -mem:width 32 -mem:lat 300 2 ../../../vortex/exe/vortex.exe ../../../vortex/data/ref/lendian1.raw
sim-outorder -redir:sim gshareVortex32 -fastfwd 50000000 -max:inst 65000000 -bpred 2lev -bpred:2lev 1 32 5 1 -mem:width 32 -mem:lat 300 2 ../../../vortex/exe/vortex.exe ../../../vortex/data/ref/lendian1.raw
sim-outorder -redir:sim gshareVortex128 -fastfwd 50000000 -max:inst 65000000 -bpred 2lev -bpred:2lev 1 128 7 1 -mem:width 32 -mem:lat 300 2 ../../../vortex/exe/vortex.exe ../../../vortex/data/ref/lendian1.raw
sim-outorder -redir:sim gshareVortex512 -fastfwd 50000000 -max:inst 65000000 -bpred 2lev -bpred:2lev 1 512 9 1 -mem:width 32 -mem:lat 300 2 ../../../vortex/exe/vortex.exe ../../../vortex/data/ref/lendian1.raw
sim-outorder -redir:sim gshareVortex2048 -fastfwd 50000000 -max:inst 65000000 -bpred 2lev -bpred:2lev 1 2048 11 1 -mem:width 32 -mem:lat 300 2 ../../../vortex/exe/vortex.exe ../../../vortex/data/ref/lendian1.raw