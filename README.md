# fastq_finder

A program to quickly search the first read header of a fastq file to match an instrument ID and a run number

## Static binary for centos6/7 and ubuntu 12+

[Download Latest Static Binary](https://github.com/martinjvickers/fastq_finder/releases/download/v0.0.1/fastq_finder_v0.0.1.tar.gz)

```
[martin@x250 dev]$ wget https://github.com/martinjvickers/fastq_finder/releases/download/v0.0.1/fastq_finder_v0.0.1.tar.gz
[martin@x250 dev]$ tar xvf fastq_finder_v0.0.1.tar.gz
[martin@x250 dev]$ ./fastq_finder 
fastq finder - Fastq match
==========================
    fastq finder -i totest.fastq.gz -id HWI-ST665R -r 135 [OPTIONS]
    Try 'fastq finder --help' for more information.

VERSION
    Last update: April 2017
    fastq finder version: 0.0.1
    SeqAn version: 2.2.1
ERROR: Could not open the file. 

```


## Compile from source

Getting this to compile on a ubuntu machine;

```
sudo apt-get install git g++ build-essential cmake zlib1g-dev libbz2-dev libboost-all-dev
git clone https://github.com/seqan/seqan.git seqan
git clone https://github.com/martinjvickers/fastq_finder.git
cd fastq_finder
cmake ../fastq_finder -DCMAKE_MODULE_PATH=../seqan/util/cmake -DSEQAN_INCLUDE_PATH=../seqan/include -DCMAKE_CXX_FLAGS=-std=c++14 -DCMAKE_BUILD_TYPE=Release
make
```

Example run from the top directory containing the fasta files you want to search for.

```
find . -regex '.*\.\(fastq\|fastq.gz\|fq\|fq.gz\)' -type f | awk '{print "./fastq_finder -i \""$i"\" -id HWI-ST665R -r 135"}'|sh
```

This will list all your fastq\|fastq.gz\|fq\|fq.gz files and then run the program looking for the instrument id HWI-ST665R and the run 135. Unless there is an error with trying to read the input file (e.g. unexpected end of file or weird character in the sequence file) you should only see something print to screen if there is a match, like so.

```
[martin@x250 data]$ find . -regex '.*\.\(fastq\|fastq.gz\|fq\|fq.gz\)' -type f | awk '{print "fastq_finder -i \""$i"\" -id HWI-ST665R -r 123"}'|sh
./XFDZR02_Run1_tair10/XFDZR02_NoIndex_L007_R1_021.fastq.gz matches instrument ID HWI-ST665R and run_num 123
./XFDZR02_Run1_tair10/XFDZR02_NoIndex_L007_R1_034.fastq.gz matches instrument ID HWI-ST665R and run_num 123
./XFDZR02_Run1_tair10/XFDZR02_NoIndex_L007_R1_010.fastq.gz matches instrument ID HWI-ST665R and run_num 123
./XFDZR02_Run1_tair10/XFDZR02_NoIndex_L007_R1_004.fastq.gz matches instrument ID HWI-ST665R and run_num 123
```

If you want to see everything it doesn't match, add the -v flag;

```
[martin@x250 data]$ find . -regex '.*\.\(fastq\|fastq.gz\|fq\|fq.gz\)' -type f | awk '{print "fastq_finder -i \""$i"\" -id HWI-ST665R -r 123 -v"}'|sh
...
./XFDZR02_Run1_tair10/XFDZR02_NoIndex_L007_R1_003.fastq.gz matches instrument ID HWI-ST665R and run_num 123
./XFDZR02_Run1_tair10/XFDZR02_NoIndex_L007_R1_009.fastq.gz matches instrument ID HWI-ST665R and run_num 123
./XFDZR02_Run1_tair10/XFDZR02_NoIndex_L007_R1_023.fastq.gz matches instrument ID HWI-ST665R and run_num 123
./pol5_veg_XFDZ015G/trimmed_fastq/pol5_veg_XFDZ015G_SDXF14_75.fq NO MATCH.
./pol5_veg_XFDZ015G/trimmed_fastq/pol5_veg_XFDZ015G_SDXF14_L001.fq.gz NO MATCH.
./pol5_veg_XFDZ015G/trimmed_fastq/pol5_veg_XFDZ015G_SDXF14_76.fq NO MATCH.
./pol5_veg_XFDZ015G/trimmed_fastq/pol5_veg_XFDZ015G_SDXF14_L002.fq.gz NO MATCH.
```


