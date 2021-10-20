sim-outorder -redir:sim applu.txt -config config.txt ../applu/exe/applu.exe < ../applu/data/ref/applu.in
sim-outorder -redir:sim crafty.txt -config config.txt ../crafty/exe/crafty.exe < ../crafty/data/ref/crafty.in
sim-outorder -redir:sim mesa.txt -config config.txt ../mesa/exe/mesa.exe < ../mesa/data/ref/mesa.in
sim-outorder -redir:sim vortex.txt -config config.txt ../vortex/exe/vortex.exe < ../vortex/data/ref/vortex.in
sim-outorder -redir:sim vpr.txt -config config.txt ../vpr/exe/vpr.exe < ../vpr/data/ref/vpr.in