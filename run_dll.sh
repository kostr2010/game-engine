clear
cd src-next

cd system/systems/systemDynamic/
echo "----------------- DLL COMPILING -----------------"
./compile.sh

cd ../../../
echo "----------------- MAIN COMPILING -----------------"
g++ maincraft.cpp -ldl -o maincraft
