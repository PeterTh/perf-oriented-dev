killall loadgen &> /dev/null
../build/loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
../build/loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
../build/loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
../build/loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
../build/loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
../build/loadgen mc3 workstation/sys_load_profile_workstation_excerpt.txt &> /dev/null &
#time -p nice -n 100 $1
nice -n 1000 $1
killall loadgen &> /dev/null
