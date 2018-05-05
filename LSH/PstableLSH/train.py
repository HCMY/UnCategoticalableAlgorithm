
import lsh
import pandas as pd
import numpy as np
import argparse

class Node(object):
	"""docstring for Node"""
	def __init__(self,index):
		self.idx = index
		self.buckets = {}

dpath = './test_data.csv'

parser = argparse.ArgumentParser(description='P-stable distributition train stage')

parser.add_argument('--r', default=1, type=int,help='range from 0 to r')
parser.add_argument('--lsh_nums', default=20, type=int,help='locality-sensitive hash function nums')
parser.add_argument('--vector_length', default=None, type=int,help='variable nums of your data')
parser.add_argument('--C', default=12000, type=int,help='mod reqired')
parser.add_argument('--table_size', default=20, type=int,help='hash table size')
parser.add_argument('--iter', default=5, type=int,help='round of calculate lsh')

args = parser.parse_args()

def load_data():
	data = pd.read_csv(dpath, header=None)
	data = np.asarray(data)
	return data 

import random


def train():
	data = load_data()
	model = lsh.PstableLSH()

	model.lsh_nums = args.lsh_nums
	model.r = args.r
	model.c = args.C
	model.iter = args.iter
	model.table_size = args.table_size
	model.random_r = [random.randint(-10, 10) for i in range(args.lsh_nums)]
	model.hash_table =  [Node(i) for i in range(args.table_size)]

	model = model.fit(data)


	query = np.asarray([4.7769, -5.67, 7.9179, 2.7671, 1])
	result_idx = lsh.Query(model).query(query)
	print(result_idx[0])




if __name__ == '__main__':
	train()

# e.g.: input this to your consle: python train.py --C 1200 --iter 6.........