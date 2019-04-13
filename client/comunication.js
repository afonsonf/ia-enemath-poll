const url = "http://localhost:8134";
// const url = "http://twserver.alunos.dcc.fc.up.pt:8134";

function postData(url = '', data = {}) {
    return fetch(url, {
        method: "POST", // *GET, POST, PUT, DELETE, etc.
        cache: "no-cache", // *default, no-cache, reload, force-cache, only-if-cached
        body: JSON.stringify(data) // body data type must match "Content-Type" header
    })
    .then(response => response.json()) // parses response to JSON
    .catch(error => console.error(error));
}

function getData(){
  return fetch(url)
  .then(response => response.json()) // parses response to JSON
  .catch(error => console.error(error));
}

function srv_vote(id, play) {
    let data = {"id": id, "play": play};
    //console.log(nick, pass);
    return postData(url + "/vote", data);
}
