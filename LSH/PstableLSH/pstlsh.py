

import random


class Node(object):
	"""docstring for Node"""
	def __init__(self,index):
		self.idx = index
		self.buckets = {}



'''
calculate .
'''
def manufacture_parameters(v_vector_length, r, lsh_nums):
	"""parameters:
	v_vector_length: your inpute vector's dimension 
	r: window num
	lsh_nums: lsh functions collection nums
	"""
	family_collection_parameters = []
	for lsh_count in range(lsh_nums):
		a = []
		for item in range(v_vector_length):
			a.append(random.gauss(0,1))
		b = random.uniform(0, r)
		single_lsh_para = (a,b)
		family_collection_parameters.append(single_lsh_para)

	return family_collection_parameters






