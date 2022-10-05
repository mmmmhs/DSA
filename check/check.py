import sys

from subprocess import run


def check_ans(output_file1, output_file2):
    """
        该函数用于判断两个输入文件是否相同，这里简单比对全文相等，可根据需求修改
        output_file1, output_file2 分别为判断的两个文件的文件名
        函数返回布尔值
    """
    with open(output_file1) as f:
        output1 = f.read()
    with open(output_file2) as f:
        output2 = f.read()
    return output1 == output2


if len(sys.argv) != 4:
    print("Usage: %s <program1> <program2> <makedata>" % sys.argv[0])
    print("    Example on Linux: python3 %s ./a.out \"python3 b.py\""
          "\"python3 makedata.py\"" % sys.argv[0])
    print("    Example on Windows: python3 %s a.exe \"python3 b.py\""
          "\"python3 makedata.py\"" % sys.argv[0])
    exit(1)

cnt = 0

while cnt < 100:
    cnt += 1
    print("Running Case #%d ... " % cnt, end="")

    run(sys.argv[3], stdout=open("input.txt", "w"),
        shell=True).check_returncode()

    run(sys.argv[1], stdin=open("input.txt"), stdout=open("output1.txt", "w"),
        timeout=5, shell=True).check_returncode()

    run(sys.argv[2], stdin=open("input.txt"), stdout=open("output2.txt", "w"),
        timeout=5, shell=True).check_returncode()

    if not check_ans("output1.txt", "output2.txt"):
        print("Wrong")
        break
    print("OK")
