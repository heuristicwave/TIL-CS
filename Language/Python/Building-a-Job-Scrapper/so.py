import requests
from bs4 import BeautifulSoup

URL = f"https://stackoverflow.com/jobs?q=python&sort=i"


def get_last_page():
    result = requests.get(URL)
    soup = BeautifulSoup(result.text, "html.parser")
    pages = soup.find("div", {"class": "s-pagination"}).find_all("a")
    # finish before last one # print last one : (pages[-1])
    #pages = pages[0:-1]
    # strip=True : get rid of endline
    last_page = pages[-2].get_text(strip=True)
    return int(last_page)


def extract_job(html):
    title = html.find(
        "h2", {"class": "mb4 fc-black-800 fs-body3"}).find("a")["title"]
    company, location = html.find(
        "h3", {"class": "fc-black-700 fs-body1 mb4"}).find_all("span", recursive=False)  # find only first level span
    company = company.get_text(strip=True)
    location = location.get_text(strip=True)
    job_id = html['data-jobid']
    return {'title': title, 'company': company, 'location': location, 'apply_link': f"https://stackoverflow.com/jobs/{job_id}"}


def extract_jobs(last_page):
    jobs = []
    for page in range(last_page):
        print(f"Scrapping SO Page: {page}")
        result = requests.get(f"{URL}&pg={page+1}")
        soup = BeautifulSoup(result.text, "html.parser")
        results = soup.find_all("div", {"class": "-job"})
        for result in results:
            # print(result["data-jobid"])
            job = extract_job(result)
            jobs.append(job)
    return jobs


def get_jobs():
    last_page = get_last_page()
    # Originally last_page is correct, but i'll give it 2 as a test
    jobs = extract_jobs(2)
    return jobs
