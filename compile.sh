find "./src" -name "*.cpp" -exec sh -c ' for file; do 
dir=$(dirname "$file") 
output_dir="build/$dir"
if [ ! -d "$output_dir" ]; then 
mkdir -p "$output_dir" 
fi
g++ -c "$file" -o "build/${file%.cpp}.o" 
done 
' sh {} +