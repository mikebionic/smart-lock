const url = location.host

function openRequest(){
	$.ajax({
	  type : 'GET',
	  url : `http://${url}/door_action/?command=open_door`,
	});
}

$('.doorActionBtn').click(function(e) {
	console.log("click")
	openRequest();
})