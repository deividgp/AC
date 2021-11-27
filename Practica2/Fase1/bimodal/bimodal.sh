#Applu
#sim-outorder -redir:sim bimodalApplu -fastfwd 50000000 -max:inst 65000000 -bpred:bimod 8 -mem:width 32 -mem:lat 300 2 ../../../applu/exe/applu.exe < ../../../applu/data/ref/applu.in
#Crafty
#sim-outorder -redir:sim bimodalCrafty -fastfwd 50000000 -max:inst 65000000 -bpred:bimod 8 -mem:width 32 -mem:lat 300 2 ../../../crafty/exe/crafty.exe < ../../../crafty/data/ref/crafty.in
#Mesa
#sim-outorder -redir:sim bimodalMesa -fastfwd 50000000 -max:inst 65000000 -bpred:bimod 8 -mem:width 32 -mem:lat 300 2 ../../../mesa/exe/mesa.exe -frames 1000 -meshfile ../../../mesa/data/ref/mesa.in -ppmfile ../../../mesa/data/ref/mesa.ppm
#Vpr
#sim-outorder -redir:sim bimodalVpr -fastfwd 50000000 -max:inst 65000000  -bpred bimod -bpred:bimod 8 -mem:width 32 -mem:lat 300 2 ../../../vpr/exe/vpr.exe ../../../vpr/data/ref/net.in ../../../vpr/data/ref/arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2
#Vortex
sim-outorder -redir:sim bimodalVortex -fastfwd 50000000 -max:inst 65000000 -bpred bimod -bpred:bimod 8 -mem:width 32 -mem:lat 300 2 ../../../vortex/exe/vortex.exe ../../../vortex/data/ref/lendian1.raw