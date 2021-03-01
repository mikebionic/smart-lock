const express = require('express')
const bodyParser = require('body-parser')

const { Resource, Res_price, Rp_acc_attendance } = require('./sequelize')

const app = express()
app.use(bodyParser.json())


app.post('/api/resource', (req, res) => {
	console.log(req.body)
})


app.get('/api/resources/', (req, res) => {
	Resource.findAll().then(resources => res.json(resources))
})


app.get('/api/attendances/', (req, res) => {
	Rp_acc_attendance.findAll().then(attendances => res.json(attendances))
})


app.get('/esp/door/', (req, res) => {
	console.log("door open called")
	console.log(req.query.device_key)
	console.log(req.query.command)
	console.log(req.query.data)
})


app.listen(3000, () => {
	console.log('running..')
})