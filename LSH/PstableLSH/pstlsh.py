

import random
import numpy as np

class Node(object):
	"""docstring for Node"""
	def __init__(self,index):
		self.idx = index
		self.buckets = {}




class PstableLSH(object):
	"""docstring for PstableLSH"""
	def __init__(self, r, lsh_nums):
		self.r = r
		self.lsh_nums = lsh_nums
		self.v_vector_length = None


	@property
	def lsh_nums(self):
		return self._lsh_nums

	@lsh_nums.setter
	def lsh_nums(self, nums):
		if not isinstance(nums, int):
			raise TypeError("expected a int")
		self._lsh_nums = nums



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
		for lsh_count in range(self.lsh_nums):
			a = []
			for item in range(self.v_vector_length):
				a.append(random.gauss(0,1))
			b = random.uniform(0, self.r)
			single_lsh_para = (a,b)
			family_collection_parameters.append(single_lsh_para)

		return family_collection_parameters


	'''
	description:
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
			hash_val = (np.dot(vector,a)+b) // self.r
			hash_vals.append(hash_val)

		return hash_vals


	def mdoel_saver(self):
		"""ub viewable parameters

		"""
		#TODO






