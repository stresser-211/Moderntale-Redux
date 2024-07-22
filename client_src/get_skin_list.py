import os

def find_list_files(directory):
	list_files = []
	for root, _, files in os.walk(directory):
		for file in files:
			if file.endswith(".skin"):
				list_files.append(os.path.join(root, file))
	return list_files

def write_to_file(file_list):
	with open("../skin/skinlist.txt", "w") as f:
		for file in file_list:
			file = file.replace("\\", "/")
			f.write(file + "??")

if __name__ == "__main__":
	write_to_file(find_list_files("../"))
