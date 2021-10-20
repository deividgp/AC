sim-outorder -redir:sim applu.txt -config config.txt ../applu/exe/applu.exe < applu.in > applu.out 2> applu.err
sim-outorder -redir:sim crafty.txt -config config.txt ../crafty/exe/crafty.exe < crafty.in > crafty.out 2> crafty.err
sim-outorder -redir:sim mesa.txt -config config.txt ../mesa/exe/mesa.exe < mesa.in > mesa.out 2> mesa.err
sim-outorder -redir:sim vortex.txt -config config.txt ../vortex/exe/vortex.exe < vortex.in > vortex.out 2> vortex.err
sim-outorder -redir:sim vpr.txt -config config.txt ../vpr/exe/vpr.exe < vpr.in > vpr.out 2> vpr.err