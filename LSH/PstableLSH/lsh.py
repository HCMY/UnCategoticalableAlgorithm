

import random
import numpy as np


"""
theories:implement from here: https://en.wikipedia.org/wiki/Locality-sensitive_hashing
hash method: random projection hash
reference :https://www.cnblogs.com/wt869054461/p/8148940.html 
"""

class PstableLSH(object):
	"""docstring for PstableLSH"""
	def __init__(self, r=None,
		lsh_nums=None, 
		C=None, 
		table_size=None, 
		round_times=None, 
		vector_length=None):

		self._r = r
		self._lsh_nums = lsh_nums
		self._v_vector_length = vector_length
		self._c = C
		self._table_size = table_size
		self._random_r = None
		self._hash_table = None
		self._iter = round_times
	


	@property
	def lsh_nums(self):
		return self._lsh_nums

	@lsh_nums.setter
	def lsh_nums(self, nums):
		if not isinstance(nums, int):
			raise TypeError("expected a int")
		self._lsh_nums = nums

	@property
	def r(self):
		return self._r

	@r.setter
	def r(self, r_val):
		#DO something
		self._r = r_val


	@property
	def v_vector_length(self):
		return self._v_vector_length

	@v_vector_length.setter
	def v_vector_length(self, v_len):
		#do something
		self._v_vector_length = v_len

	@property
	def c(self):
		return self._c

	@c.setter
	def c(self, C):
		self._c = C

	@property
	def table_size(self):
		return self._table_size

	@table_size.setter
	def table_size(self, table_size):
		self._table_size = table_size


	@property
	def iter(self):
		return self._iter

	@iter.setter
	def iter(self, times):
		self._iter = times

	@property
	def random_r(self):
		return  self._random_r

	@random_r.setter
	def random_r(self, random_r_set):
		self._random_r = random_r_set

	@property
	def hash_table(self):
		return  self._hash_table

	@hash_table.setter
	def hash_table(self, table):
		self._hash_table =table


	'''
	calculate .
	'''
	def manufacture_parameters(self):
		"""un viewable parameters:
		v_vector_length: your inpute vector's dimension, which could be obtain from your input data matrix
		r: window num
		lsh_nums: lsh functions collection nums
		"""
		family_collection_parameters = []
		for lsh_count in range(self._lsh_nums):
			a = []
			for item in range(self._v_vector_length):
				a.append(random.gauss(0,1))
			b = random.uniform(0, self._r)
			single_lsh_para = (a,b)
			family_collection_parameters.append(single_lsh_para)

		return family_collection_parameters


	'''
	description: random projection hash
	reference :https://www.cnblogs.com/wt869054461/p/8148940.html 
	'''
	def calculate_hashval(self, vector, lsh_func_collection):
		"""parameters
		vector: a vector format data from data matrix
		lsh_func_collection: LSH hash function collections, which's num is K probobaly.
		"""
		hash_vals = []
		for lsh_func in lsh_func_collection:
			a = lsh_func[0]
			b = lsh_func[1]
			hash_val = (np.inner(vector,a)+b) // self._r
			hash_vals.append(hash_val)

		return hash_vals

	"""
	save all required parameters
	"""
	def mdoel_saver(self, path):
		"""ub viewable parameters

		"""
		#TODO


	def hash_to_table(self, hash_vals):
		"""
		return hash to which table
		"""
		return int(sum([(hash_vals[i] * self._random_r[i]) \
						for i in range(self._lsh_nums)]) % self._c)


	"""
    train the algorithm
	"""
	def fit(self, matrix):
		rows, cols = matrix.shape
		self._v_vector_length = cols
		hash_func_collection = []

		for round in range(self._iter):
			lsh_parameters = self.manufacture_parameters()
			hash_func_collection.append(lsh_parameters)
			for data_idx in range(rows):
				hash_val = self.calculate_hashval(matrix[data_idx], lsh_parameters)
				key = self.hash_to_table(hash_val)
				bucket_idx = key % self._table_size
				node = self._hash_table[bucket_idx]

				if key in node.buckets:
					bucket = node.buckets[key]
					bucket.append(data_idx)
				else:
					node.buckets[key] = [data_idx]
		# package model
		model_complier = {'hash_func_collection':hash_func_collection, 
						   'hash_table':self._hash_table,
						   'vector_length':self._v_vector_length,
						    'C':self._c, 
						    'iter':self._iter, 
						    'r':self._r, 
						    'lsh_nums':self._lsh_nums, 
						  	'random_r':self._random_r, 
						  	'table_size':self._table_size,
						  	}


		return model_complier




"""
query the most simility data from all the bucket
also could recise the code to return the tarhet bucket
"""
class Query(PstableLSH):
	def __init__(self, model):
		super(Query, self).__init__(r=model['r'],
									lsh_nums=model['lsh_nums'], 
									C=model['C'], 
									table_size=model['table_size'], 
									round_times=model['iter'],
									vector_length=model['vector_length'],
									)
		self.hash_groups = model['hash_func_collection']
		self.hash_table = model['hash_table']
		self._random_r = model['random_r']

	def query(self, vector):
		"""papameters
		vector: query vector, data type is numpy.array
		
		"""
		data_idx = []
		for hash_funcs in self.hash_groups:
			hash_vals = self.calculate_hashval(vector, hash_funcs)
			key = self.hash_to_table(hash_vals)
			bucket_idx = key % self._table_size
			if key in self.hash_table[bucket_idx].buckets:
				data_idx.append(self.hash_table[bucket_idx].buckets[key])

		return data_idx















