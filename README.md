# fastq_finder

Getting this to compile on work machine;

```
~/cmake-3.6.0-rc2-Linux-x86_64/bin/cmake ../fastq_finder -DCMAKE_MODULE_PATH=../seqan/util/cmake -DSEQAN_INCLUDE_PATH=../seqan/include -DCMAKE_CXX_FLAGS=-std=c++14 -DCMAKE_BUILD_TYPE=Release
```

Example run

```
find . -regex '.*\.\(fastq\|fastq.gz\|fq\|fq.gz\)' -type f | awk '{print "./fastq_finder -i "$i" -id HWI-ST665R -r 135"}'|sh
```
