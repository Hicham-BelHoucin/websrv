const data = [
	{
		id: 1,
		login: 'hbel-hou',
		fullname: 'Hicham Bel houcin',
	},
	{
		id: 2,
		login: 'obeaj',
		fullname: 'Ousama Beaj',
	},
	{
		id: 3,
		login: 'imabid',
		fullname: 'Imad Abid',
	}
]

function appendContributors(fullname, login)
{
	const container = document.createElement('div')
	const child = document.createElement("img");
	const span = document.createElement("span");

	span.setAttribute('class', 'name')
	span.innerText = fullname
	container.setAttribute('class', 'Card')
	child.setAttribute('src', `/img/${login}.png`)
	child.setAttribute('class', 'profile-img')

	const el = document.getElementById("root");
	container.appendChild(child)
	container.appendChild(span)
	el.appendChild(container);
}

data.map(item => appendContributors(item.fullname, item.login))