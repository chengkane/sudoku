
class sudoku(object):
	#fil=lambda data: filter(lambda x : x!=0, data)
	def __init__(self,data):
		self.bo=[ data[i*9:i*9+9] for i in range(9) ]
		self.r=[ self.fil(i) for i in self.bo]
		temp=[ data[i::9] for i in range(9) ]
		self.c=[ self.fil(i) for i in temp ]

		b=[[],[],[],]
		for i in range(0,9,3):
			for j in range(0,9,3):
				temp=[]
				for ii in range(3):
					for jj in range(3):
						temp.append(self.bo[i+ii][j+jj])
				b[i//3].append(self.fil(temp))
		self.b=[]
		for i in range(9):
			self.b.append([])
		for i in range(9):
			for j in range(9):
				self.b[i].append(b[i//3][j//3])
		self.rs=[]
	def put(self,x,y,f):
		if (f not in self.r[x] 
				and f not in self.c[y] 
				and f not in self.b[x][y] ):
			self.bo[x][y]=f
			self.r[x].add(f)
			self.c[y].add(f)
			self.b[x][y].add(f)
			return True
		return False
	def remove(self,x,y,f):
		self.bo[x][y]=0
		self.r[x].remove(f)
		self.c[y].remove(f)
		self.b[x][y].remove(f)
	def display(self):
		for i in self.bo:
			print i
		if self.rs:
			print('the result is')
			for i in self.rs:
				print i
	def fil(self,data):
		rs=set(data)
		try:
			rs.remove(0)
		except:
			pass
		finally:
			return rs

def find(a,x,y):
	if x==9:
		print('find it')
		a.rs=copy.deepcopy(a.bo)
		return True
		pass
	
	xx,yy=(x,y+1) if y<9-1 else (x+1,0)
	
	if a.bo[x][y]!=0:
		return find(a,xx,yy)
		pass
	if x<9:
		for i in range(1,10):
			if(a.put(x,y,i)):
				rs=find(a,xx,yy)
				a.remove(x,y,i)
				if rs:
					return True
		return False


import copy
import time

bo=[]
while len(bo)<9*9 :
	temp=list(raw_input())
	temp=filter(lambda x: x.isdigit(), temp)
	bo+=temp
del bo[9*9:]
bo=map(int,bo)

a=sudoku(bo)
start=time.clock()
find(a,0,0)
start=time.clock()-start
a.display()
rs='time used:%.4f s'%(start)
print rs

