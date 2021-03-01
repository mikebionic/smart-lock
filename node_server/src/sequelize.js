const Sequelize = require('sequelize')

const Resource_Model = require('./models/Resource')
const Res_price_Model = require('./models/Res_price')
const Rp_acc_attendance_Model = require('./models/Rp_acc_attendance')

const { USERNAME, PASSWORD, HOST, PORT, DB_NAME, DIALECT } = require('./constants')

const sequelize = new Sequelize(`${DIALECT}://${USERNAME}:${PASSWORD}@${HOST}:${PORT}/${DB_NAME}`)

const Resource = Resource_Model(sequelize, Sequelize)
const Res_price = Res_price_Model(sequelize, Sequelize)
const Rp_acc_attendance = Rp_acc_attendance_Model(sequelize, Sequelize)

Resource.hasMany(Res_price)

sequelize.sync({force: false})
.then(() => {
	console.log('tables created')
})

console.log(Rp_acc_attendance)

module.exports = {
	Resource,
	Res_price,
	Rp_acc_attendance
}