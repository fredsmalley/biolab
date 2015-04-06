import urllib as ul
import os.path as op

listFile = open("../in/participants.tsv", "r")
participantList = []
websiteList = []
saveFileList = []

for line in listFile:
	participantList.append(line[:-1])

participantList.pop(0)		# remove title line
listFile.close()

for item in participantList:
	websiteList.append("https://my.pgp-hms.org/profile/" + item)

for item in websiteList:
	saveFileList.append(item[item.find("profile/") + 8:] + ".html")

print len(saveFileList), "files to download"

participantDir = "../in/PGP-participants/"
fname = ""

for item in websiteList:
	fname = participantDir + item[item.find("profile/") + 8:] + ".html"
	if op.isfile(fname):
		ul.urlretrieve(item, fname)
