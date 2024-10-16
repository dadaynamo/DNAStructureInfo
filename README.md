# DNAStructureInfo
DNAStructureInfo is a C++ tool that analyzes DNA sequences, extracting key metrics like entropy, local entropy, and compressibility rate. It generates a summary table to help researchers and bioinformaticians better understand the complexity and structure of the DNA.

## Installation
Use make command to compile the cpp program

## Usage: 
### With Makefile
```
make comparison
```

```
make individual
```

### Classic Execution
```
./mainDNAStructureInfo [option] [argument] | ...
```

Options:
  --help                        Show this help message and exit.
  
  --type <type>                 Specify the type of sequences (Raw, Eds, Eds-intensive, Test)
                                 Example: --type [R, E, I, T]

  --output <outputfile>          Specify the name of the output file without the extension.
                                 Example: --output result


  --version                      Display the version of the program and exit.

### Examples:
```
./mainDNAStructureInfo --type C --typeOut T --typeIn E --profile A --outputName output --inOrigin input --inListComp test1 test2 test3
```
```
  ./mainDNAStructureInfo --type I --typeOut T --typeIn E --profile A --outputName output --inOrigin input
```