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
  
  --type                        Specify the type of Procedure (Comparison, Individual)
                                 Example: --type [C , I]

  --typeOut                      Specify the extention of the output file (.txt, .csv).
                                 Example: --typeOut [C , T]

  --typeIn                      Specify the extention of the file in input (.eds, .txt)
                                Example: --typeIn [E, T]

  --profile                     Specify the style of the output table (General, Advanced)
                                Example: --profile [G, A]      
  
  --outputName                  Specify the name of the ouput file without extention
                                Example --outputName finalout
  
  --inOrigin                    Specify in a comparison test the original file to compare
                                --inOrigin original

  --inListComp                  Specify the name list of the file compressed
                                --inListComp comp1 comp2 comp3

  --version                      Display the version of the program and exit.

### Examples:
```
./mainDNAStructureInfo --type C --typeOut T --typeIn E --profile A --outputName output --inOrigin input --inListComp test1 test2 test3
```
```
./mainDNAStructureInfo --type I --typeOut T --typeIn E --profile A --outputName output --inOrigin input
```