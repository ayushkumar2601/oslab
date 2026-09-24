# Day 1: Self-Assessment with General Purpose Utilities in UNIX-like Systems

**1. What is a directory?**
A directory is a location for storing files on your computer.

**2. Significance of HOME variable: The Home Directory.**
The HOME variable stores the absolute path to the current user's home directory.

**3. Operations on directories:**
**a. Check the current directory.**
```bash
pwd
```
**b. Change the current directory.**
```bash
cd /path/to/dir
```
**c. Create new directory (s).**
```bash
mkdir newdir
```
**d. Remove directory (s).**
```bash
rmdir emptydir
```

**4. Absolute pathnames, Relative pathnames.**
Absolute pathnames start from the root `/`, whereas relative pathnames start from the current directory.

**5. What is a command?**
A command is a directive to a computer program to perform a specific task.

**6. What is ls Command?**
`ls` lists directory contents.

**7. How to switch Directories?**
```bash
cd new_directory
```

**8. How to display the user currently working on the system?**
```bash
whoami
```

**9. How to display the name and version of your operating system?**
```bash
uname -a
```

**10. How to display the calendar of a month or year?**
```bash
cal
```

**11. How to display the current system date and time in a variety of formats?**
```bash
date +"%Y-%m-%d %H:%M:%S"
```

**12. How to use echo to display a message on the terminal?**
```bash
echo "Hello"
```

**Handling Ordinary Files: The File System:**

**1. The File. What’s in a (File) name?**
A file is a collection of data. A filename uniquely identifies it within a directory.

**2. Display, create, copy, move, delete, and rename file.**
```bash
cat file.txt
touch newfile.txt
cp file1 file2
mv file1 file2
rm file.txt
mv oldname newname
```

**3. Counting Lines, Words and Characters of file(s).**
```bash
wc file.txt
```

**4. Comparing Two Files.**
```bash
cmp file1 file2
```

**5. What is Common between two files?**
```bash
comm file1 file2
```

**6. Compressing, decompressing and archiving file(s).**
```bash
gzip file.txt
gunzip file.txt.gz
tar -cvf archive.tar file1 file2
```

**Basic File Attributes : File Ownership. File Permissions.**
```bash
chown user file.txt
chmod 755 file.txt
```

**File Filters: Filter Commands: head, tail, cut, sort, uniq, tr, grep, sed.**
```bash
head -n 5 file.txt
tail -n 5 file.txt
cut -d' ' -f1 file.txt
sort file.txt
uniq file.txt
tr 'a-z' 'A-Z' < file.txt
grep "pattern" file.txt
sed 's/old/new/g' file.txt
```
