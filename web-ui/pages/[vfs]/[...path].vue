<template>
    <div>
        <h1>Файлы в: {{ fullPath }}</h1>
        <ul>
        <li v-for="file in files" :key="file.name">
            {{ file.name }} — {{ file.size }} байт
        </li>
        </ul>
    </div>
</template>

<script setup>
    import { onMounted, ref, computed } from 'vue'
    import { useRoute } from 'vue-router'

    const route = useRoute()
    const files = ref([])

    const vfsName = route.params.vfs

    // subPath — массив, если он есть, иначе пустой массив
    const rawPath = route.params.path
    const subPathArray = computed(() =>
    Array.isArray(rawPath)
        ? rawPath
        : typeof rawPath === 'string'
        ? [rawPath]
        : []
    )
    const subPath = computed(() => subPathArray.value.join('/'))

    const fullPath = computed(() => `/${vfsName}/${subPath.value}`)

    onMounted(async () => {
    const apiPath = `/api/${vfsName}${subPath.value ? '/' + subPath.value : ''}`
    console.log(apiPath)
    const res = await fetch(apiPath)

    if (res.ok) {
        files.value = await res.json()
        console.log(files.value)
    } else {
        files.value = []
    }
    })
</script>
