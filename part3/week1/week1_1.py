FILENAME = 'jobs.txt'

class Job:
    def __init__(self, weight, length):
        self.weight = int(weight)
        self.length = int(length)
        self.diff   = int(weight) - int(length)

def readFileAndReturnJobsArray(fileName):
    file = open(fileName, 'r')
    lines = file.read().splitlines()
    # line1: Number of Jobs
    # line2,3,...: w_i l_i
    jobNumber = lines[0]
    textJobs = lines[1:]
    jobs = []
    for textJob in textJobs:
        textJob = textJob.split(' ')
        job = Job(int(textJob[0]), int(textJob[1]))
        jobs.append(job)
    return jobs

def calcObjectiveFunction(jobs):
    completionTime = 0
    sumOfWeigthtedCompletionTime = 0
    for job in jobs:
        completionTime += job.length
        sumOfWeigthtedCompletionTime += job.weight * completionTime
    return sumOfWeigthtedCompletionTime

if __name__ == '__main__':
    jobs = readFileAndReturnJobsArray(FILENAME)
    # sort by diff
    # if diff_i == diff_j compare w_i with w_j
    jobs = sorted(jobs, key=lambda job: (job.diff, job.weight), reverse=True)
    sumOfWeigthtedCompletionTime = calcObjectiveFunction(jobs)
    print(sumOfWeigthtedCompletionTime)


