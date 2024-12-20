#!/bin/bash

# About dataset https://clickhouse.com/docs/en/getting-started/example-datasets/metrica
# Here we can find some useful information, like names of columns, their types, and so on.

mkdir datasets
curl https://datasets.clickhouse.com/hits/tsv/hits_v1.tsv.xz | unxz --threads=`nproc` > datasets/hits_v1.tsv
