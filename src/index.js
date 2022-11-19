const data = [
	{
		id: 1,
		githubName: 'Hicham-BelHoucin',
		fullname: 'Hicham Bel houcin',
	},
	{
		id: 2,
		githubName: 'BEAJousama',
		fullname: 'Ousama Beaj',
	},
	{
		id: 3,
		githubName: 'imabid99',
		fullname: 'Imad Abid',
	}
]

function appendContributors(fullname, githubName)
{
	const container = document.createElement('div')
	const child = document.createElement("img");
	const span = document.createElement("span");

	span.innerText = fullname

	container.setAttribute('class', 'Card')
	child.setAttribute('src', `https://github.com/${githubName}.png`)
	child.setAttribute('class', 'profile-img')

	const el = document.getElementById("root");
	container.appendChild(child)
	container.appendChild(span)
	el.appendChild(container);
}



data.map(item => appendContributors(item.fullname, item.githubName))