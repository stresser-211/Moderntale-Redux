import os
import argparse

def skin_find(directory):
	list_files = []
	for root, _, files in os.walk(directory):
		for file in files:
			if file.endswith(".skin"):
				list_files.append(os.path.join(root, file))
	return list_files
def skin_get(file_list):
	with open("../skin/skinlist.txt", "w") as f:
		for file in file_list:
			file = file.replace("\\", "/")
			f.write(file + "??")
def skin_pack(skin, *args):
	with open(skin, "wb") as f:
		for arg in args:
			f.write(b"SK!N&<<" + arg.encode("utf-8") + b"?>>")
			with open(arg, "rb") as file:
				f.write(file.read())
	return 0
def skin_unpack(skin):
	tmp = os.path.join(os.getenv("TEMP"), "Moderntale Redux/", skin)
	os.makedirs(tmp, exist_ok=True)
	with open(skin, "rb") as f:
		content = f.read()
	parts = content.split(b"SK!N&name<<")
	for part in parts[1:]:

		delimiter_pos = part.find(b"?>>")
		if delimiter_pos == -1:
			delimiter_pos - 1
		filename = part[:delimiter_pos].decode("utf-8")
		file_content = part[delimiter_pos + 3:]
		file_path = tmp + "/" + filename
		with open(file_path, "wb") as file:
			file.write(file_content)
	return 0
def main():
	parser = argparse.ArgumentParser(description="Feet.")
	parser.add_argument("-list", action="store_true")
	parser.add_argument("-p", nargs="+", type=str)
	parser.add_argument("-x", action="store_true")
	parser.add_argument("-s", nargs="?", type=str)
	args = parser.parse_args()
	if args.list:
		skin_get(skin_find("../"))
	if not args.s:
		return 2
	if args.p:
		return skin_pack(args.s, *args.p)
	if args.x:
		return skin_unpack(args.s)
	return 0
if __name__ == "__main__":
	main()